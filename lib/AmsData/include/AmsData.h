#ifndef _AMSDATA_H
#define _AMSDATA_H

#include "Arduino.h"
#include <Timezone.h>

enum AmsType {
    AmsTypeAutodetect = 0x00,
    AmsTypeAidon = 0x01,
    AmsTypeKaifa = 0x02,
    AmsTypeKamstrup = 0x03,
    AmsTypeIskra = 0x08,
    AmsTypeLandisGyr = 0x09,
    AmsTypeSagemcom = 0x0A,
    AmsTypeCustom = 0x88,
    AmsTypeUnknown = 0xFF
};

enum AmsField : uint32_t {
    None = 0,
    AmsActiveImportPower = 1 << 0,
    AmsReactiveImportPower = 1 << 1,
    AmsActiveExportPower = 1 << 2,
    AmsReactiveExportPower = 1 << 3,
    AmsPowerFactor = 1 << 4,
    AmsActiveImportCounter = 1 << 5,
    AmsReactiveImportCounter = 1 << 6,
    AmsActiveExportCounter = 1 << 7,
    AmsReactiveExportCounter = 1 << 8,
    AmsL1Voltage = 1 << 9,
    AmsL2Voltage = 1 << 10,
    AmsL3Voltage = 1 << 11,
    AmsL1Current = 1 << 12,
    AmsL2Current = 1 << 13,
    AmsL3Current = 1 << 14,
    AmsL1Current = 1 << 15,
    AmsL1PowerFactor = 1 << 15,
    AmsL2PowerFactor = 1 << 16,
    AmsL3PowerFactor = 1 << 17,
    AmsL1ActiveImportPower = 1 << 18,
    AmsL2ActiveImportPower = 1 << 19,
    AmsL3ActiveImportPower = 1 << 20,
    AmsL1ActiveExportPower = 1 << 21,
    AmsL2ActiveExportPower = 1 << 22,
    AmsL3ActiveExportPower = 1 << 23,

    AmsListId = 1 << 28,
    AmsMeterId = 1 << 29,
    AmsPackageTimestamp = 1 << 30,
    AmsMeterTimestamp = 1u << 31
};

inline AmsField operator |(AmsField a, AmsField b)
{
    return static_cast<AmsField>(static_cast<int>(a) | static_cast<int>(b));
}

inline AmsField operator &(AmsField a, AmsField b)
{
    return static_cast<AmsField>(static_cast<int>(a) & static_cast<int>(b));
}

inline AmsField& operator |=(AmsField& a, AmsField b)
{
    return a = a | b;
}

class AmsData {
public:
    AmsData();

    void apply(AmsData& other);

    unsigned long getLastUpdateMillis();

    time_t getPackageTimestamp();

    uint8_t getListType();

    String getListId();
    String getMeterId();
    uint8_t getMeterType();
    String getMeterModel();

    time_t getMeterTimestamp();

    uint32_t getActiveImportPower();
    uint32_t getReactiveImportPower();
    uint32_t getActiveExportPower();
    uint32_t getReactiveExportPower();

    float getL1Voltage();
    float getL2Voltage();
    float getL3Voltage();

    float getL1Current();
    float getL2Current();
    float getL3Current();

    float getPowerFactor();
    float getL1PowerFactor();
    float getL2PowerFactor();
    float getL3PowerFactor();

    float getL1ActiveImportPower();
    float getL2ActiveImportPower();
    float getL3ActiveImportPower();

    float getL1ActiveExportPower();
    float getL2ActiveExportPower();
    float getL3ActiveExportPower();

    double getActiveImportCounter();
    double getReactiveImportCounter();
    double getActiveExportCounter();
    double getReactiveExportCounter();

    bool isThreePhase();
    bool isTwoPhase();

    double getAmsNumberField(AmsField field);
    String getAmsStringField(AmsField field);
    bool hasAmsField(AmsField field);

    int8_t getLastError();
    void setLastError(int8_t);

protected:
    unsigned long lastUpdateMillis = 0;
    unsigned long lastList2 = 0;
    uint8_t listType = 0, meterType = AmsTypeUnknown;
    time_t packageTimestamp = 0;
    String listId = "", meterId = "", meterModel = "";
    time_t meterTimestamp = 0;
    uint32_t activeImportPower = 0, reactiveImportPower = 0, activeExportPower = 0, reactiveExportPower = 0;
    float l1voltage = 0, l2voltage = 0, l3voltage = 0, l1current = 0, l2current = 0, l3current = 0;
    float l1activeImportPower = 0, l2activeImportPower = 0, l3activeImportPower = 0;
    float l1activeExportPower = 0, l2activeExportPower = 0, l3activeExportPower = 0;
    float powerFactor = 0, l1PowerFactor = 0, l2PowerFactor = 0, l3PowerFactor = 0;
    double activeImportCounter = 0, reactiveImportCounter = 0, activeExportCounter = 0, reactiveExportCounter = 0;
    bool threePhase = false, twoPhase = false, counterEstimated = false;

    int8_t lastError = 0x00;
    uint8_t lastErrorCount = 0;
    AmsField available = AmsField::None;
};

#endif
