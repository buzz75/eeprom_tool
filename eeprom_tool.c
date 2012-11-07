
/**
 * @file eeprom_tool.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/ioctl.h>

#define EEPROM_IO    0xA2

/*
#define AT24_IOCTL_WRITE_UUID                _IOW(EEPROM_IO, 0x01, char*)
#define AT24_IOCTL_WRITE_BT_MAC              _IOW(EEPROM_IO, 0x02, char*)
#define AT24_IOCTL_WRITE_SN                  _IOW(EEPROM_IO, 0x03, char*)
#define AT24_IOCTL_WRITE_SNWB                _IOW(EEPROM_IO, 0x04, char*)
#define AT24_IOCTL_WRITE_MANUFACTURE_DATE    _IOW(EEPROM_IO, 0x05, char*)
#define AT24_IOCTL_WRITE_IMEI                _IOW(EEPROM_IO, 0x06, char*)
#define AT24_IOCTL_WRITE_BOARD_ID            _IOW(EEPROM_IO, 0x07, char*)
#define AT24_IOCTL_WRITE_PRODUCT_SKU         _IOW(EEPROM_IO, 0x08, char*)
#define AT24_IOCTL_WRITE_L_SENSOR            _IOW(EEPROM_IO, 0x09, char*)
#define AT24_IOCTL_WRITE_G_SENSOR            _IOW(EEPROM_IO, 0x0a, char*)
#define AT24_IOCTL_WRITE_WV_Device_ID        _IOW(EEPROM_IO, 0x0b, char*)
*/
/*
#define AT24_IOCTL_WRITE_BLSN                _IOW(EEPROM_IO, 0x01, char*)
#define AT24_IOCTL_WRITE_USB_DEBUG           _IOW(EEPROM_IO, 0x02, char*)
#define AT24_IOCTL_WRITE_BT_MAC              _IOW(EEPROM_IO, 0x03, char*)
#define AT24_IOCTL_WRITE_SNWB                _IOW(EEPROM_IO, 0x04, char*)
#define AT24_IOCTL_WRITE_IMEI                _IOW(EEPROM_IO, 0x05, char*)
#define AT24_IOCTL_WRITE_BOARD_ID            _IOW(EEPROM_IO, 0x06, char*)
#define AT24_IOCTL_WRITE_PRODUCT_SKU         _IOW(EEPROM_IO, 0x07, char*)
#define AT24_IOCTL_WRITE_MANUFACTURE_DATE    _IOW(EEPROM_IO, 0x08, char*)
#define AT24_IOCTL_WRITE_G_SENSOR            _IOW(EEPROM_IO, 0x09, char*)
#define AT24_IOCTL_WRITE_L_SENSOR            _IOW(EEPROM_IO, 0x0a, char*)
*/
#define AT24_IOCTL_WRITE_BLSN                _IOW(EEPROM_IO, 0x01, char*)
#define AT24_IOCTL_WRITE_USB_DEBUG           _IOW(EEPROM_IO, 0x02, char*)
#define AT24_IOCTL_WRITE_BT_MAC              _IOW(EEPROM_IO, 0x03, char*)
#define AT24_IOCTL_WRITE_SNWB                _IOW(EEPROM_IO, 0x04, char*)
#define AT24_IOCTL_WRITE_MANUFACTURE_DATE    _IOW(EEPROM_IO, 0x05, char*)
#define AT24_IOCTL_WRITE_IMEI                _IOW(EEPROM_IO, 0x06, char*)
#define AT24_IOCTL_WRITE_BOARD_ID            _IOW(EEPROM_IO, 0x07, char*)
#define AT24_IOCTL_WRITE_PRODUCT_SKU         _IOW(EEPROM_IO, 0x08, char*)
#define AT24_IOCTL_WRITE_L_SENSOR            _IOW(EEPROM_IO, 0x09, char*)
#define AT24_IOCTL_WRITE_G_SENSOR            _IOW(EEPROM_IO, 0x0a, char*)

/*#define AT24_IOCTL_WRITE_UUID                _IOW(EEPROM_IO, 0x01, char*)
#define AT24_IOCTL_WRITE_BT_MAC              _IOW(EEPROM_IO, 0x02, char*)
#define AT24_IOCTL_WRITE_SN                  _IOW(EEPROM_IO, 0x03, char*)
#define AT24_IOCTL_WRITE_SNWB                _IOW(EEPROM_IO, 0x04, char*)
#define AT24_IOCTL_WRITE_MANUFACTURE_DATE    _IOW(EEPROM_IO, 0x05, char*)
#define AT24_IOCTL_WRITE_IMEI                _IOW(EEPROM_IO, 0x06, char*)
#define AT24_IOCTL_WRITE_BOARD_ID            _IOW(EEPROM_IO, 0x07, char*)
#define AT24_IOCTL_WRITE_PRODUCT_SKU         _IOW(EEPROM_IO, 0x08, char*)
#define AT24_IOCTL_WRITE_L_SENSOR            _IOW(EEPROM_IO, 0x09, char*)
#define AT24_IOCTL_WRITE_G_SENSOR            _IOW(EEPROM_IO, 0x0a, char*)
#define AT24_IOCTL_WRITE_WV_Device_ID        _IOW(EEPROM_IO, 0x0b, char*)
#define AT24_IOCTL_WRITE_BLSN                _IOW(EEPROM_IO, 0x0c, char*)
#define AT24_IOCTL_WRITE_USB_DEBUG           _IOW(EEPROM_IO, 0x0d, char*)
*/

/* EEPROM DATA LENGTH */
/*
#define LENGTH_UUID			16
#define LENGTH_BT_MAC			6
#define LENGTH_SN			14
#define LENGTH_SNWB			22
#define LENGTH_MANUFACTURE_DATE		4
#define LENGTH_IMEI			8
#define LENGTH_BOARD_ID			1
#define LENGTH_PRODUCT_SKU		2
#define LENGTH_L_SENSOR			10
#define LENGTH_G_SENSOR			75
#define LENGTH_WV_Device_ID		32
*/
#define LENGTH_BLSN                     22
#define LENGTH_USB_DEBUG                1
#define LENGTH_RESERVE                  11
#define LENGTH_BT_MAC                   6
#define LENGTH_SNWB                     22
#define LENGTH_IMEI                     8
#define LENGTH_BOARD_ID		        1
#define LENGTH_PRODUCT_SKU              2
#define LENGTH_MANUFACTURE_DATE		4
#define LENGTH_G_SENSOR      		94
#define LENGTH_L_SENSOR         	24

/* EEPROM DATA LENGTH (HEX) */
#define LENGTH_HEX_USB_DEBUG		2
#define LENGTH_HEX_BT_MAC	    	12
#define LENGTH_HEX_MANUFACTURE_DATE	8
#define LENGTH_HEX_IMEI			15
#define LENGTH_HEX_BOARD_ID		2
#define LENGTH_HEX_PRODUCT_SKU		4
#define LENGTH_HEX_G_SENSOR		188
#define LENGTH_HEX_L_SENSOR		48

#define BUUF_SIZE			188

#define DEV_NAME "/dev/at24_dev"


int check_length(char *input, unsigned int length);
int read_eeprom(FILE *stream, char *dev_node, char *buf, int size);
int is_hex(char c);
void show_eeprom(char *str ,char *title, char *format, int size);
int char2hex(char *str, char *data, int length);
unsigned int atohex(const char *s, int length);
char *lower_case(char *str);


int main(int argc, char **argv)
{
	FILE *stream = NULL;
	char *rw = NULL;
	char *cmd = NULL;
	char *data = NULL;
	char *data_hex = NULL;
	int fd_acc = -1;

	char line_buf[BUUF_SIZE];

	// read most have 3 input
	if (argc < 3) {
		printf("Usage: eeprom_tool R [Device Node]\n");
		printf("       eeprom_tool W [Device Node] [Value]\n\n");
		return 1;
	}

	// convert to lower case
	rw = lower_case(argv[1]);
	cmd  = lower_case(argv[2]);

	// write most have 4 input
	if (argc < 4 && strcmp(rw, "w") == 0) {
		printf("Usage: eeprom_tool W [Device Node] [Value]\n\n");
		return 1;
	}

	// Read EEPROM
	if (strcmp(rw, "r") == 0) {
		if (strcmp(cmd, "boardlevelserialnumber") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/BoardLevelSerialNumber", line_buf, LENGTH_BLSN))
				show_eeprom(line_buf, "BoardLevelSerialNumber", "%c", LENGTH_BLSN);
			else if (read_eeprom(stream, "/sys/at24/BoardLevelSerialNumber", line_buf, LENGTH_BLSN))
				show_eeprom(line_buf, "BoardLevelSerialNumber", "%c", LENGTH_BLSN);
			else 
				printf("Cannot open Device node\n");
				}
		else if (strcmp(cmd, "usbdebug") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeporm/USBDebug", line_buf, LENGTH_HEX_USB_DEBUG))
				show_eeprom(line_buf, "USBDebug", "%c", LENGTH_HEX_USB_DEBUG );
			else if (read_eeprom(stream, "/sys/at24/USBDebug", line_buf, LENGTH_HEX_USB_DEBUG))
				show_eeprom(line_buf, "USBDebug", "%c", LENGTH_HEX_USB_DEBUG );
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "btmac") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/BTMAC", line_buf, LENGTH_HEX_BT_MAC))
				show_eeprom(line_buf, "BTMAC", "%c", LENGTH_HEX_BT_MAC);
			else if (read_eeprom(stream, "/sys/at24/BTMAC", line_buf, LENGTH_HEX_BT_MAC))
				show_eeprom(line_buf, "BTMAC", "%c", LENGTH_HEX_BT_MAC);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "serialnumberwithoutbarcode") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/SerialNumberwithoutBarcode", line_buf, LENGTH_SNWB))
				show_eeprom(line_buf, "SerialNumberwithoutBarcode", "%c", LENGTH_SNWB);
			else if (read_eeprom(stream, "/sys/at24/SerialNumberwithoutBarcode", line_buf, LENGTH_SNWB))
				show_eeprom(line_buf, "SerialNumberwithoutBarcode", "%c", LENGTH_SNWB);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "manufacturedate") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/ManufactureDate", line_buf, LENGTH_HEX_MANUFACTURE_DATE))
				show_eeprom(line_buf, "ManufactureDate", "%c", LENGTH_HEX_MANUFACTURE_DATE);
			else if (read_eeprom(stream, "/sys/at24/ManufactureDate", line_buf, LENGTH_HEX_MANUFACTURE_DATE))
				show_eeprom(line_buf, "ManufactureDate", "%c", LENGTH_HEX_MANUFACTURE_DATE);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "boardid") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/BoardID", line_buf, LENGTH_HEX_BOARD_ID))
				show_eeprom(line_buf, "BoardID", "%c", LENGTH_HEX_BOARD_ID);
			else if (read_eeprom(stream, "sys/at24/BoardID", line_buf, LENGTH_HEX_BOARD_ID))
				show_eeprom(line_buf, "BoardID", "%c", LENGTH_HEX_BOARD_ID);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "imeiwithbarcode") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/IMEIwithBarcode", line_buf, LENGTH_HEX_IMEI))
				show_eeprom(line_buf, "IMEIwithBarcode", "%c", LENGTH_HEX_IMEI);
			else if (read_eeprom(stream, "/sys/at24/IMEIwithBarcode", line_buf, LENGTH_HEX_IMEI))
				show_eeprom(line_buf, "IMEIwithBarcode", "%c", LENGTH_HEX_IMEI);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "productsku") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/ProductSKU", line_buf, LENGTH_HEX_PRODUCT_SKU))
				show_eeprom(line_buf, "ProductSKU", "%c", LENGTH_HEX_PRODUCT_SKU);
			else if (read_eeprom(stream, "/sys/at24/ProductSKU", line_buf, LENGTH_HEX_PRODUCT_SKU))
				show_eeprom(line_buf, "ProductSKU", "%c", LENGTH_HEX_PRODUCT_SKU);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "lightsensor") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/LightSensor", line_buf, LENGTH_HEX_L_SENSOR))
				show_eeprom(line_buf, "LightSensor", "%c", LENGTH_HEX_L_SENSOR);
			else if (read_eeprom(stream, "/sys/at24/LightSensor", line_buf, LENGTH_HEX_L_SENSOR))
				show_eeprom(line_buf, "LightSensor", "%c", LENGTH_HEX_L_SENSOR);
			else
				printf("Cannot open Device node\n");
		}
		else if (strcmp(cmd, "gsensor") == 0) {
			if (read_eeprom(stream, "/sys/dev-info_eeprom/GSensor", line_buf, LENGTH_HEX_G_SENSOR))
				show_eeprom(line_buf, "GSensor", "%c", LENGTH_HEX_G_SENSOR);
			else if (read_eeprom(stream, "/sys/at24/GSensor", line_buf, LENGTH_HEX_G_SENSOR))
				show_eeprom(line_buf, "GSensor", "%c", LENGTH_HEX_G_SENSOR);
			else
				printf("Cannot open Device node\n");
		}
		else {
			printf("Usage: eeprom_tool R [Device Node]\n");
		}
	// Write EEPROM
	}else if (strcmp(rw, "w") == 0) {
		data = argv[3];

		if ((fd_acc = open(DEV_NAME, O_RDWR)) < 0) {
			printf("Open Error!\n");
		}
		else if (strcmp(cmd, "boardlevelserialnumber") == 0) {
			if (check_length(data, LENGTH_BLSN)) {
				printf("Input Length Error.\n");
			}
			else {
				if ((ioctl(fd_acc, AT24_IOCTL_WRITE_BLSN, data)) < 0)
					printf("AT24_IOCTL_WRITE_BLSN ioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "usbdebug") == 0) {
			if (check_length(data, LENGTH_HEX_USB_DEBUG)) {
				printf("Input Length Error. \n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_USB_DEBUG);
				if (!char2hex(data, data_hex, LENGTH_USB_DEBUG))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_USB_DEBUG, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_USB_DEBUG ioctl calling fail. \n");
			}
		}
		else if (strcmp(cmd, "btmac") == 0) {
			if (check_length(data, LENGTH_HEX_BT_MAC)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_BT_MAC);
				if (!char2hex(data, data_hex, LENGTH_BT_MAC))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_BT_MAC, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_BT_MACioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "serialnumberwithoutbarcode") == 0) {
			if (check_length(data, LENGTH_SNWB)) {
				printf("Input Length Error.\n");
			}
			else {
				if ((ioctl(fd_acc, AT24_IOCTL_WRITE_SNWB, data)) < 0)
					printf("AT24_IOCTL_WRITE_SNWBioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "manufacturedate") == 0) {
			if (check_length(data, LENGTH_HEX_MANUFACTURE_DATE)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_MANUFACTURE_DATE);
				if (!char2hex(data, data_hex, LENGTH_MANUFACTURE_DATE))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_MANUFACTURE_DATE, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_MANUFACTURE_DATEioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "imeiwithbarcode") == 0) {
			if (check_length(data, LENGTH_HEX_IMEI)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_IMEI);
				if (!char2hex(data, data_hex, LENGTH_IMEI))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_IMEI, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_IMEIioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "boardid") == 0) {
			if (check_length(data, LENGTH_HEX_BOARD_ID)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_BOARD_ID);
				if (!char2hex(data, data_hex, LENGTH_BOARD_ID))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_BOARD_ID, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_BOARD_IDioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "productsku") == 0) {
			if (check_length(data, LENGTH_HEX_PRODUCT_SKU)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_PRODUCT_SKU);
				if (!char2hex(data, data_hex, LENGTH_PRODUCT_SKU))
					printf("Input Value is not HEX.\n");
				else if ((ioctl(fd_acc, AT24_IOCTL_WRITE_PRODUCT_SKU, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_PRODUCT_SKUioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "lightsensor") == 0) {
			if (check_length(data, LENGTH_HEX_L_SENSOR)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_L_SENSOR);
				if (!char2hex(data, data_hex, LENGTH_L_SENSOR))
					printf("Input Value is not HEX\n");
				if ((ioctl(fd_acc, AT24_IOCTL_WRITE_L_SENSOR, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_L_SENSORioctl calling fail.\n");
			}
		}
		else if (strcmp(cmd, "gsensor") == 0) {
			if (check_length(data, LENGTH_HEX_G_SENSOR)) {
				printf("Input Length Error.\n");
			}
			else {
				data_hex = malloc(sizeof(char) * LENGTH_G_SENSOR);
				if (!char2hex(data, data_hex, LENGTH_G_SENSOR))
					printf("Input Value is not HEX\n");
				if ((ioctl(fd_acc, AT24_IOCTL_WRITE_G_SENSOR, data_hex)) < 0)
					printf("AT24_IOCTL_WRITE_G_SENSOR calling fail.\n");
			}
		}
		else {
			printf("Usage: eeprom_tool W [Device Node] [Value]\n");
		}
	}
	//Not read and write. Error!
	else {
		printf("Usage: eeprom_tool R [Device Node]\n");
		printf("       eeprom_tool W [Device Node] [Value]\n");
	}

	if (data_hex != NULL)
		free(data_hex);
	if (fd_acc != -1)
		close(fd_acc);
	
	printf("\n\n");
	
	return 0;
}

/**
 * @brief check length
 *
 * @param input input string
 * @param length compare size
 * 
 * @return 1 is different
 */
int check_length(char *input, unsigned int length) {
	return strlen(input) == length ? 0 : 1;
}

/**
 * @brief Using fopen access eeropm
 *
 * @param stream FILE
 * @param dev_node opened device node
 * @param buf read file buf
 * @param size read file size
 * 
 * @return 0 is open error.
 */
int read_eeprom(FILE *stream, char *dev_node, char *buf, int size)
{
	if (!(stream = fopen(dev_node, "r")))
		return 0;

	fread(buf, size, 1, stream);
	fclose(stream);
	return 1;
}

/**
 * @brief check input is hex or not
 *
 * @param c check char
 *
 * @return 1 is hex, 0 is not hex (0~f)
 */
int is_hex(char c) {
	if ((c >= '0' && c <= '9') || 
	    (c >= 'a' && c <= 'f') ||
	    (c >= 'A' && c <= 'F'))
		return 1;
	return 0;
}

/**
 * @brief display eeprom value
 *
 * @param str print string
 * @param title print title
 * @param format print format
 * @param size size of string
 *
 */
void show_eeprom(char *str ,char *title, char *format, int size)
{
	int i = 0;

	printf("%s:\n", title);
	for (i = 0; i < size; i++)
		printf(format, str[i]);
	printf("\n");
}

/**
 * @brief convert hex from string to int array(2)
 *
 * @param str convert string
 * @param data hex string buff
 * @param length string length
 *
 * @return 0 is converted fail, 1 is success
 */
int char2hex(char *str, char *data, int length)
{
	int i = 0;
	char tmp[2];

	for (i = 0; i < (int)strlen(str); i++) {
		if (!is_hex(str[i]))
			return 0;
	}

	for (i = 0; i < length; i++) {
		tmp[0] = str[i * 2];
		tmp[1] = str[i * 2 + 1];
		data[i] = atohex(tmp, 2);
	}
	return 1;
}

/**
 * @brief convert hex from string to int
 *
 * @param s convert string
 * @param length string length
 *
 * @return converted value
 */
unsigned int atohex(const char *s, int length)
{
	int rv = 0;
	int i = 0;

	for (i = 0; i < length; i++) {
		int v = s[i] - '0';
		if (v > 9)
			v -= 7;
		v &= 15; /* in case it's lower case */
		rv = rv * 16 + v;
	}

	return rv;
}

/**
 * @brief convert to lower case
 *
 * @param str convert string
 *
 * @return lower case string
 */
char *lower_case(char *str)
{
	int i = 0;

	for (i = 0; str[i] != '\0'; i++)
		str[i] = (char)tolower(str[i]);

	return str;
}
