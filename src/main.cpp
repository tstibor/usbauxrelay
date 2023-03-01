/*
  Other AUX projects (hardware/software) with additional information:
  i) NexStar Direct Telescope Mount Control
  https://sites.google.com/site/wayneholder/nexstar-direct-telescope-mount-control

  ii) Homebrew Mount-USB Connection for AUX-Port
  https://www.cloudynights.com/topic/812944-homebrew-mount-usb-connection-for-aux-port/

  iii) NextDriver: An Arduino-based controller for Celestron CG5-series equatorial mounts.
  https://github.com/juanmb/nextdriver/

  Code is published under GPL3 license (see LICENSE).
*/
#include <Arduino.h>

#define PIN_AUX_SELECT	5
#define PIN_AUX_TX	6
#define PIN_AUX_RX	7

#define USB_BAUDRATE	19200
#define AUX_BAUDRATE	19200
#define UsbSerial	Serial
#define AuxSerial	Serial1

/* Output AUX protocol logging via softserial TX/RX. */
#ifdef AUX_DEBUG
#include <SoftwareSerial.h>
#include "nexstaraux.h"

#define PIN_DEBUG_RX		0
#define PIN_DEBUG_TX		1
#define DEBUG_SERIAL_BAUDRATE	19200

SoftwareSerial DebugSerial(PIN_DEBUG_RX, PIN_DEBUG_TX);
uint8_t serial_aux_pos = 0;
uint8_t serial_usb_pos = 0;
struct aux_packet serial_aux_packet;
struct aux_packet serial_usb_packet;

#define SERIAL_AUX_LOG(c) AuxParse(c, &serial_aux_packet, &serial_aux_pos, "aux")
#define SERIAL_USB_LOG(c) AuxParse(c, &serial_usb_packet, &serial_usb_pos, "usb")

uint8_t AuxChecksum(const struct aux_packet *aux_packet)
{
    int result = 0;
    uint8_t *data = (uint8_t*)aux_packet;

    for (int i = 1; i < aux_packet->length + 2; i++) {
        result += data[i];
    }

    return -result & 0xff;
}

void AuxLog(const char *s, struct aux_packet *aux_packet)
{
    static char msg[176] = { 0 };
    static char cmd[32] = { 0 };

    strcpy(cmd, AUX_COMMAND_STR(aux_packet->dest, aux_packet->cmd));
    if (!strcmp(cmd, "UNKNOWN")) {
	strcpy(cmd, AUX_COMMAND_STR(aux_packet->src, aux_packet->cmd));
    }

    memset(msg, 0, sizeof(msg));
    if (aux_packet->length == 3) {
	sprintf(msg, "[%08lums,%s] %s -> %s, cmd %s: "
		"AUX packet <0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x> (checksum 0x%02x)\n",
		millis(), s,
		AUX_DEVICE_STR(aux_packet->src),
		AUX_DEVICE_STR(aux_packet->dest),
		cmd,
		aux_packet->preamble,
		aux_packet->length,
		aux_packet->src,
		aux_packet->dest,
		aux_packet->cmd,
		aux_packet->checksum,
		AuxChecksum(aux_packet));
    } else {
	const uint8_t L = aux_packet->length - 0x03;
	char payload_hex[1 + (L * 5) + 1] = { 0 }; /* e.g. (0x12 0x34 0x56) */
	payload_hex[0] = '(';
	char *ptr = &payload_hex[1];

	for (uint8_t l = 0; l < L; l++) {
	    ptr += sprintf(ptr, "0x%02x ", aux_packet->payload[l]);
	}
	payload_hex[(L * 5)] = ')';
	payload_hex[(L * 5) + 1] = '\0';
	sprintf(msg, "[%08lums,%s] %s -> %s, cmd %s: "
		"AUX packet <0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, %s, 0x%02x> (checksum 0x%02x)\n",
		millis(), s,
		AUX_DEVICE_STR(aux_packet->src),
		AUX_DEVICE_STR(aux_packet->dest),
		cmd,
		aux_packet->preamble,
		aux_packet->length,
		aux_packet->src,
		aux_packet->dest,
		aux_packet->cmd,
		payload_hex,
		aux_packet->checksum,
		AuxChecksum(aux_packet));
    }

    DebugSerial.print(msg);
    DebugSerial.flush();
}

void AuxParse(uint8_t c, struct aux_packet *aux_packet, uint8_t *aux_pos, const char *s)
{
    if (c == 0x3B && *aux_pos == 0) {
	memset(aux_packet, 0, sizeof(*aux_packet));
	aux_packet->preamble = c;
	(*aux_pos)++;
    } else if (*aux_pos == 1 && aux_packet->preamble == 0x3B) {
	aux_packet->length = c;
	(*aux_pos)++;
    } else if (*aux_pos == 2 && aux_packet->preamble == 0x3B) {
	aux_packet->src = c;
	(*aux_pos)++;
    } else if (*aux_pos == 3 && aux_packet->preamble == 0x3B) {
	aux_packet->dest = c;
	(*aux_pos)++;
    } else if (*aux_pos == 4 && aux_packet->preamble == 0x3B) {
	aux_packet->cmd = c;
	(*aux_pos)++;
    } else if (*aux_pos > 4 && aux_packet->preamble == 0x3B) {
	if (*aux_pos - aux_packet->length == 2) {
	    aux_packet->checksum = c;
	    *aux_pos = 0;
	    AuxLog(s, aux_packet);
	} else {
	    aux_packet->payload[*aux_pos - 5] = c;
	    (*aux_pos)++;
	}
    }
}
#endif

/*
  The behavior of the built-in LED is reversed to the one on
   an Arduino. On the Seeed XIAO SAMD21, the pin has to be
   pulled low, whereas on other micro-controllers it has to be pulled high.
*/
void blinkCode(uint16_t ms)
{
    for (uint8_t i = 0; i < 3; i++) {
	digitalWrite(LED_BUILTIN, LOW);
	delay(ms);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(ms);
    }
}

/*
  Due to the diode/resistor tri-state wiring, transmitting
  a byte over AUX serial (UART) induces an echo receiving.
  That is, whenever AuxSerial.write(...) is called a subsequent
  dropEcho() call is mandatory.
 */
void dropEcho()
{
    while (AuxSerial.available()) {
	(void)AuxSerial.read();
    }
}

/*
  Relay Nexstar packets from AUX to USB.
 */
void AuxToUsb()
{
    uint8_t buf[64] = {0};
    uint8_t len = 0;

    while (AuxSerial.available()) {
	uint8_t c = AuxSerial.read();
#ifdef AUX_DEBUG
	SERIAL_AUX_LOG(c);
#endif
	if (UsbSerial) {
	    buf[len++] = c;
	    if (len >= sizeof(buf)) {
		UsbSerial.write(buf, len);
		UsbSerial.flush();
		len = 0;
	    }

	    if (!AuxSerial.available())
		delayMicroseconds(600);
	}
    }
    if (len && UsbSerial) {
	UsbSerial.write(buf, len);
	UsbSerial.flush();
    }
}

/*
  Claiming transmitting AUX packet by waiting for select pin low
  and setting selecting for output.
*/
void AuxTxClaim()
{
    while (digitalRead(PIN_AUX_SELECT) == LOW)
	delay(1);

    digitalWrite(PIN_AUX_SELECT, LOW);
    pinMode(PIN_AUX_SELECT, OUTPUT);
    digitalWrite(PIN_AUX_SELECT, LOW);
}

/*
  Relay Nexstar packets from USB to AUX.
 */
void UsbToAux()
{
    if (!UsbSerial.available())
	return;

    AuxTxClaim();

    while (UsbSerial.available()) {
	uint8_t c = UsbSerial.read();
#ifdef AUX_DEBUG
        SERIAL_USB_LOG(c);
#endif
	AuxSerial.write(c);
	dropEcho();
    }

    AuxSerial.flush();

    /* End TX transaction. Flip to input pin. */
    pinMode(PIN_AUX_SELECT, INPUT);
}

void setup()
{
    /* Setup AUX serial RX/TX. */
    AuxSerial.begin(AUX_BAUDRATE, SERIAL_8N2);
    pinMode(PIN_AUX_SELECT, INPUT);

    /* Setup USB serial RX/TX. */
    UsbSerial.begin(USB_BAUDRATE);

    /* Blink build-in LED 3 times with 300ms delay and then switch
       off for signaling correct startup. */
    pinMode(LED_BUILTIN, OUTPUT);
    blinkCode(300);

#ifdef AUX_DEBUG
    /* Setup soft serial RX/TX debug output. */
    DebugSerial.begin(DEBUG_SERIAL_BAUDRATE);
    DebugSerial.write("Nexstar USB AUX relay version 0.1 successfully initialized\n");
    DebugSerial.flush();
#endif
}

void loop()
{
    UsbToAux();
    AuxToUsb();
}
