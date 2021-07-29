//#define DECODE_NEC
//#define DECODE_RC5
//#define DECODE_RC6
#define NO_LEGACY_COMPATIBILITY
#define IR_RECEIVE_PIN 5

#include <IRremote.h>
#include "HID-Project.h"
#define code_index_length 27
uint64_t code_index[code_index_length] = {
  0x0000000C0E0E0010, // power button
  0x0000000D0E0E0010, // mute
  0x000000140E0E0010, // volume up
  0x000000150E0E0010, // volume down
  0x000000110E0E0010, // menu
  0x000000450E0E0010, // right arrow
  0x000000440E0E0010, // left arrow
  0x000000420E0E0010, // up arrow
  0x000000430E0E0010, // down arrow
  0x000000460E0E0010, // OK
  0x000000490E0E0010, // Play/Pause
  0x000000410E0E0010, // next
  0x000000400E0E0010, // previous
  0x000000B50E0E0010, // exit
  0x0000000B0E0E0010, // return
  0x000000120E0E0010, // page up
  0x000000130E0E0010, // page down
  0x000000000E0E0010, // enter
  0x000000A30E0E0010, // F11
  0x000000A20E0E0010, // F5
  0x000000010E0E0010, // youtube
  0x000000020E0E0010, // netflix
  0x000000040E0E0010, // widnow swap
  0x000000050E0E0010, // all windows
  0x000000060E0E0010, // on screen keyboard
  0x000000160E0E0010, // info
  0x000000B20E0E0010, // vimeo


};

uint32_t current_event_time = 0, last_event_time = 0, last_data_time = 0, last_execution_time = 0;
uint64_t current_event_code = 0, last_event_code = 0;
uint8_t current_event_button_state = 0, last_event_button_state = 0;

uint8_t repeat_action = 0;

uint8_t logarithmic_delay_run(uint32_t max_delay, uint32_t speed = 50000) {
  if ( ((millis() - last_execution_time) > (millis() - current_event_time)) || (millis() - last_execution_time) > min(speed / (millis() - current_event_time), max_delay)) {
    last_execution_time = millis();
    return 1;
  }
  return 0;
}


void button_press() {
  Serial.println("BUTTON DOWN!");
  repeat_action = 0;

  if (current_event_code == 0x000000140E0E0010) {    // volume up
    if (logarithmic_delay_run(250)) Consumer.write(MEDIA_VOLUME_UP);
    repeat_action = 1;
  }
  else if (current_event_code == 0x000000150E0E0010) {  // volume down
    if (logarithmic_delay_run(250)) Consumer.write(MEDIA_VOLUME_DOWN);
    repeat_action = 1;
  }
  else if (current_event_code == 0x0000000D0E0E0010) Consumer.write(MEDIA_VOLUME_MUTE);   // mute
  else if (current_event_code == 0x000000490E0E0010 || current_event_code == 0x0000001300120007) Consumer.write(MEDIA_PLAY_PAUSE); // play/pause
  else if (current_event_code == 0x000000410E0E0010 || current_event_code == 0x0000001600120007) Consumer.write(MEDIA_NEXT); // play next
  else if (current_event_code == 0x000000400E0E0010 || current_event_code == 0x0000001200120007) Consumer.write(MEDIA_PREVIOUS); // play previous
  else if (current_event_code == 0x000000110E0E0010) Consumer.write(CONSUMER_BROWSER_HOME); // menu

  else if (current_event_code == 0x0000000B0E0E0010) Keyboard.write(HID_KEYBOARD_ESCAPE); // return
  else if (current_event_code == 0x000000120E0E0010) Keyboard.write(HID_KEYBOARD_PAGE_UP);  // channel +
  else if (current_event_code == 0x000000130E0E0010) Keyboard.write(HID_KEYBOARD_PAGE_DOWN); // channel -

  // else if (current_event_code == 0x000000060000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_RIGHTARROW); repeat_action=1; }
  // else if (current_event_code == 0x000000020000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_UPARROW); repeat_action=1; }
  // else if (current_event_code == 0x000000040000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_LEFTARROW); repeat_action=1; }
  // else if (current_event_code == 0x000000080000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_DOWNARROW); repeat_action=1; }
  else if (current_event_code == 0x000000000E0E0010) Keyboard.write(HID_KEYBOARD_ENTER); // 0

  else if (current_event_code == 0x000000A30E0E0010) Keyboard.write(HID_KEYBOARD_F11); // blue button
  else if (current_event_code == 0x000000F000040007) Keyboard.write(HID_KEYBOARD_F5); // yellow button
  //else if (current_event_code == 0x0000004500040007) Keyboard.write(HID_KEYBOARD_LEFT_ALT);

  //else if (current_event_code == 0x0000009500040007) System.write(HID_SYSTEM_SLEEP);

  else if (current_event_code == 0x000000010E0E0010) { // 1
    Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(50);

    Keyboard.println("https://youtube.com/");
  }
  else if (current_event_code == 0x000000020E0E0010) { // 2
    Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(50);

    Keyboard.println("https://netflix.com/");
  }
  else if (current_event_code == 0x000000B20E0E0010) { // subtitle
    Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    Keyboard.press('t');
    Keyboard.releaseAll();
    delay(50);

    Keyboard.println("https://vimeo.com/");
  }
  else if (current_event_code == 0x000000040E0E0010) { // 4
    Keyboard.press(HID_KEYBOARD_LEFT_ALT);
    Keyboard.press(HID_KEYBOARD_TAB);
    Keyboard.releaseAll();
  }
  else if (current_event_code == 0x000000050E0E0010) { // 5
    Keyboard.press(HID_KEYBOARD_LEFT_GUI);
    Keyboard.press(HID_KEYBOARD_TAB);
    Keyboard.releaseAll();
  }
  else if (current_event_code == 0x000000060E0E0010) { // 6
    Keyboard.press(HID_KEYBOARD_LEFT_GUI);
    Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    Keyboard.press('o');
    Keyboard.releaseAll();
  }
 
  else if (current_event_code == 0x000000B50E0E0010) { // exit/close
    Keyboard.press(HID_KEYBOARD_LEFT_ALT);
    Keyboard.press(HID_KEYBOARD_F4);
    Keyboard.release(HID_KEYBOARD_F4);
    Keyboard.releaseAll();
  }
  else if (current_event_code == 0x0000003900040007) {
    Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
    Keyboard.press(HID_KEYBOARD_PAGE_DOWN);
    Keyboard.releaseAll();
  }
  else if (current_event_code == 0x0000000B00040007) {
    Keyboard.press(HID_KEYBOARD_LEFT_GUI);
    Keyboard.press('l');
    Keyboard.releaseAll();
  }
  else if (current_event_code == 0x000000420E0E0010) {
    if (logarithmic_delay_run(300, 500)) Mouse.move(0, -1);  //up
    repeat_action = 1;
  }
  else if (current_event_code == 0x000000440E0E0010) {
    if (logarithmic_delay_run(300, 500)) Mouse.move(-1, 0);  //left
    repeat_action = 1;
  }
  else if (current_event_code == 0x000000430E0E0010) {
    if (logarithmic_delay_run(300, 500)) Mouse.move(0,  1);  //down
    repeat_action = 1;
  }
  else if (current_event_code == 0x000000450E0E0010) {
    if (logarithmic_delay_run(300, 500)) Mouse.move(1,  0);  //right arrow
    repeat_action = 1;
  }
  else if (current_event_code == 0x000000460E0E0010) Mouse.click(MOUSE_LEFT); // OK
  else if (current_event_code == 0x000000160E0E0010) Mouse.click(MOUSE_RIGHT); // info
  else return 0;
  return 1;

}
void button_release() {
  Serial.println("BUTTON UP!");

  repeat_action = 0;
}

void IREventHandler() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.resume();
      return;
    }

    uint64_t new_event_code = 0;
    memcpy(&new_event_code, &IrReceiver.decodedIRData, sizeof(IrReceiver.decodedIRData.protocol) + sizeof(IrReceiver.decodedIRData.address) + sizeof(IrReceiver.decodedIRData.command));

    if (new_event_code == current_event_code && current_event_button_state == 1) {//nothing new happend, just a repeat code
      last_data_time = millis();
      IrReceiver.resume();
      return;
    }
    uint32_t low = new_event_code;
    uint32_t high = (new_event_code >> 32);
    char buf[32];
    sprintf(buf, "0x%08lX%08lX", high, low);
    Serial.println(buf);
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    int i = 0;
    for (i = 0; i < code_index_length; i++) {
      if (code_index[i] == new_event_code) break;
    }
    if (i == code_index_length) {
      IrReceiver.resume();
      return;
    }

    if (current_event_button_state == 1) {
      last_event_time = current_event_time;
      current_event_time = millis();

      last_event_code = current_event_code;

      last_event_button_state = current_event_button_state;
      current_event_button_state = 0;

      button_release();
    }

    last_event_code = current_event_code;
    current_event_code = new_event_code;

    last_event_time = current_event_time;
    current_event_time = millis();
    last_data_time = current_event_time;

    last_event_code = current_event_code;

    last_event_button_state = current_event_button_state;
    current_event_button_state = 1;

    button_press();

    IrReceiver.resume();
  } else if (millis() - last_data_time > 200 && current_event_button_state == 1) {
    last_event_time = current_event_time;
    current_event_time = millis();
    last_event_code = current_event_code;

    last_event_button_state = current_event_button_state;
    current_event_button_state = 0;

    button_release();

  }

}



void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  IrReceiver.begin(IR_RECEIVE_PIN);

  Mouse.begin();
  Keyboard.begin();
  Consumer.begin();
  System.begin();
  Serial.begin(2000000);
}

void loop() {
  IREventHandler();
  if (repeat_action) {
    button_press();
  }

}
