#include "mks_wifi_gcodes.h"

#ifdef MKS_WIFI

#include "../../module/printcounter.h"
#include "../../libs/duration_t.h"

const uint8_t pak[5] = { 0xA5, 0x07, 0x00, 0x00, 0xFC };

const char m997_idle[]     = "M997 IDLE\n";
const char m997_printing[] = "M997 PRINTING\n";
const char m997_pause[]    = "M997 PAUSE\n";
const char m115_firmware[] = "FIRMWARE_NAME:ANET EX\n";

char *createFilename(char * const buffer, const dir_t &p);

bool longName2DosName(const char* longname, char* dosname) {
  dir_t dir;

  card.getroot().rewind();
  card.cdroot();

  while(card.getWorkDir().readDir(&dir, card.longFilename) > 0) {
    if(!strcmp((char *)card.longFilename, longname)) {
      createFilename(dosname, dir);
      MKS_WIFI_DEBUG("Found file %s (DOS: %s)", card.longFilename, dosname);
      return true;
    }  
  }

  MKS_WIFI_DEBUG("[ERROR] Can't find file %s", longname);
  return false;
}

void mks_m991() {
  char tempBuf[128];
  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  if (target_extruder < 0) return;

  memset(tempBuf, 0, 128);

  sprintf((char *)tempBuf,"T:%d /%d B:%d /%d T0:%d /%d T1:0 /0 @:0 B@:0\n", 
  (int)Temperature::degHotend(target_extruder),Temperature::degTargetHotend(target_extruder),
  (int)Temperature::degBed(),Temperature::degTargetBed(),
  (int)Temperature::degHotend(target_extruder),Temperature::degTargetHotend(target_extruder));

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  mks_wifi_out_add((uint8_t*)tempBuf, strlen(tempBuf));
}

void mks_m105() {
  char tempBuf[128];
  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  
  if(target_extruder < 0) return;

  memset(tempBuf, 0, 128);

  sprintf((char *)tempBuf,"T:%.1f /%.1f B:%.1f /%.1f T0:%.1f /%.1f T1:0.0 /0.0 @:0 B@:0\n",
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder),
  Temperature::degBed(),(float)Temperature::degTargetBed(),
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder));

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  mks_wifi_out_add((uint8_t*)tempBuf, strlen(tempBuf));
}

void mks_m997() {
  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();
  if(CardReader::isPrinting()) {
    mks_wifi_out_add((uint8_t*)m997_printing, strlen(m997_printing));
  } else if(CardReader::isPaused()) {
    mks_wifi_out_add((uint8_t*)m997_pause, strlen(m997_pause));
  } else {
    mks_wifi_out_add((uint8_t*)m997_idle, strlen(m997_idle));
  }
}

void mks_m115() {
  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  mks_wifi_out_add((uint8_t*)m115_firmware, strlen(m115_firmware));
}

void mks_m992() {
  if(!CardReader::isPrinting())
    return;

  char buffer[32];
  uint32_t duration_sec = print_job_timer.duration();
  uint16_t hours = duration_sec / 3600;
  uint16_t minutes = (duration_sec - hours * 3600) / 60;
  uint16_t seconds = (duration_sec - hours * 3600 - minutes * 60);

  sprintf((char*)buffer, "M992 %02d:%02d:%02d\r\n", hours, minutes, seconds);

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  mks_wifi_out_add((uint8_t*)buffer,strlen(buffer));
}

void mks_m994() {
  if(!CardReader::isPrinting())
    return;

  char buffer[256];
  char filename[128];

  CardReader::GetSelectedFilename(filename);

  sprintf((char*)buffer, "M994 %s;%ld\n", filename, CardReader::GetSelectedFilesize());

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  mks_wifi_out_add((uint8_t *)buffer,strlen(buffer));
}

void mks_m27() {
  if(CardReader::isPrinting()) {
    SERIAL_ECHOPGM(STR_OK);
    SERIAL_EOL();

    SERIAL_ECHOPGM("M27 ");
    SERIAL_ECHOPGM(CardReader::percentDone());
    SERIAL_EOL();
  }
}

void mks_m30(char *filename) {
  MKS_WIFI_DEBUG("M30: %s", filename);

  if(filename[1] == ':') {
    filename += 2;
    MKS_WIFI_DEBUG("Strip volume. Result: %s", filename);
  }

  if(filename[0] == '/') {
    filename += 1;
    MKS_WIFI_DEBUG("Strip slash. Result: %s", filename);
  }
  
  if(card.isMounted()) {
    card.closefile();

    char dosname[14];
  
    if(longName2DosName(filename, dosname)) {
      MKS_WIFI_DEBUG("DOS file name: %s", dosname);
      card.removeFile(dosname);
      SERIAL_ECHOPGM(STR_OK);
      SERIAL_EOL();
    }
  }
}

void mks_m23(char *filename) {
  MKS_WIFI_DEBUG("M23: %s", filename);

  if(!card.isMounted()) {
    MKS_WIFI_DEBUG("[ERROR] Disk not mounted");
    return;
  }

  char dosname[14];
  
  if(longName2DosName(filename, dosname)) {
    MKS_WIFI_DEBUG("DOS file name: %s", dosname);
    card.openFileRead(dosname);
    SERIAL_ECHOPGM(STR_OK);
    SERIAL_EOL();
  }
}

#endif
