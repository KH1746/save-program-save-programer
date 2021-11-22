#include <Wire.h>
#include "KX122.h"
#include "BM1422AGMV.h"
#include "BM1383AGLV.h"

#define HIGH_TEMPERATURE_DEGREE (30)

KX122 KX122(KX122_DEVICE_ADDRESS_1F);
BM1422AGMV bm1422agmv(BM1422AGMV_DEVICE_ADDRESS_0F);
BM1383AGLV bm1383aglv;

float prev_acc[3];

void setup()
{
    byte rc1, rc2, rc3;

    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("Rohm BM1422AGMV Magnet Sensor sample");
    Wire.begin();
    rc1 = KX122.init();
    rc2 = bm1422agmv.init();
    rc3 = bm1383aglv.init();
    if (rc1 != 0)
    {
        Serial.println(F("KX122 initialization failed"));
        Serial.flush();
    }
    if (rc2 != 0)
    {
        Serial.println(F("BM1422AGMV initialization failed"));
        Serial.flush();
    }
    if (rc3 != 0)
    {
        Serial.println("BM1383AGLV initialization failed");
        Serial.flush();
    }
}

bool check_vibration()
{
    float vibration_power = 0;
    byte rc;

    float acc[3];
    rc = KX122.get_val(acc);
    if (rc == 0)
    {

        if (
            prev_acc[0] != 0 &&
            prev_acc[1] != 0 &&
            prev_acc[2] != 0)
        {
            vibration_power =
                sqrt(
                    pow(acc[0] - prev_acc[0], 2) +
                    pow(acc[1] - prev_acc[1], 2) +
                    pow(acc[2] - prev_acc[2], 2));
        }
    }

    prev_acc[0] = acc[0];
    prev_acc[1] = acc[1];
    prev_acc[2] = acc[2];

    return vibration_power > 1.0;
}

bool check_high_temperature()
{
    byte rc;

    float press = 0;
    float temp = 0;

    rc = bm1383aglv.get_val(&press, &temp);
    Serial.println(temp);
    return temp > HIGH_TEMPERATURE_DEGREE;
}

void loop()
{
    //rc1 = kx122.get_val(acc);
    //rc2 = bm1422agmv.get_val(mag);
    //rc3 = bm1383aglv.get_val(&press, &temp);
    if (check_vibration())
    {
        Serial.println("EARTHQUAKE");
    }

    if (check_high_temperature())
    {
        Serial.println("HIGH_TEMPERATURE");
    }
    /* if (rc1 == 0)
    {
        Serial.write("KX122 (X) = ");
        Serial.print(acc[0]);
        Serial.println(" [g]");
        Serial.write("KX122 (Y) = ");
        Serial.print(acc[1]);
        Serial.println(" [g]");
        Serial.write("KX122 (Z) = ");
        Serial.print(acc[2]);
        Serial.println(" [g]");
        Serial.println();
    }
    if (rc2 == 0)
    {
        Serial.print("BM1422AGMV XDATA=");
        Serial.print(mag[0], 3);
        Serial.println("[uT]");
        Serial.print("BM1422AGMV YDATA=");
        Serial.print(mag[1], 3);
        Serial.println("[uT]");
        Serial.print("BM1422AGMV ZDATA=");
        Serial.print(mag[2], 3);
        Serial.println("[uT]");
        Serial.println();
    }
    if (rc3 == 0)
    {
        Serial.print("BM1383AGLV (PRESS) = ");
        Serial.print(press);
        Serial.println(" [hPa]");
        Serial.print("BM1383AGLV (TEMP) =  ");
        Serial.print(temp);
        Serial.println(" [degrees Celsius]");
        Serial.println();
    }
 */
    delay(500);
}
