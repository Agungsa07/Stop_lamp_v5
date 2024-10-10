#define DEBUG 0   // Enable or disable (default) debugging output

#if DEBUG
#define PRINT(s, v)   { Serial.print(F(s)); Serial.print(v); }        // Print a string followed by a value (decimal)
#define PRINTX(s, v)  { Serial.print(F(s)); Serial.print(v, HEX); }   // Print a string followed by a value (hex)
#define PRINTB(s, v)  { Serial.print(F(s)); Serial.print(v, BIN); }   // Print a string followed by a value (binary)
#define PRINTC(s, v)  { Serial.print(F(s)); Serial.print((char)v); }  // Print a string followed by a value (char)
#define PRINTS(s)     { Serial.print(F(s)); }                         // Print a string
#else
#define PRINT(s, v)   // Print a string followed by a value (decimal)
#define PRINTX(s, v)  // Print a string followed by a value (hex)
#define PRINTB(s, v)  // Print a string followed by a value (binary)
#define PRINTC(s, v)  // Print a string followed by a value (char)
#define PRINTS(s)     // Print a string
#endif

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   D5
#define DATA_PIN  D7
#define CS_PIN    D8

const int rem = D1;   // Pin D4 (GPIO 1)
const int kanan = D2; // Pin D2 (GPIO 2)
const int kiri = D3;  // Pin D1 (GPIO 3)
int       i = 0;

/** ANimasi Stop */
byte stop_s[]   = {0xfb, 0xfb, 0xc0, 0xf8, 0xf8, 0x18, 0xf8, 0xf8};
byte stop_t[]   = {0xf3, 0xf7, 0xc6, 0xc6, 0xc6, 0xc6, 0xc7, 0xc3};
byte stop_op[]  = {0x9e, 0xdf, 0xdb, 0xdf, 0xde, 0xd8, 0xd8, 0x98};

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
#if !RUN_DEMO
#endif
#define UNIT_DELAY      15
#define SCROLL_DELAY    (3 * UNIT_DELAY)
#define MIDLINE_DELAY   (6 * UNIT_DELAY)
#define SCANNER_DELAY   (2 * UNIT_DELAY)
#define RANDOM_DELAY    (6 * UNIT_DELAY)
#define SPECTRUM_DELAY  (4 * UNIT_DELAY)
#define HEARTBEAT_DELAY (1 * UNIT_DELAY)
#define HEARTS_DELAY    (28 * UNIT_DELAY)
#define EYES_DELAY      (20 * UNIT_DELAY)
#define WIPER_DELAY     (1 * UNIT_DELAY)
#define INVADER_DELAY   (6 * UNIT_DELAY)
#define PACMAN_DELAY    (4 * UNIT_DELAY)
#define SINE_DELAY      (2 * UNIT_DELAY)

#define CHAR_SPACING     1  // pixels between characters
#define BUF_SIZE        75  // character buffer size


uint32_t prevTimeAnim = 0;    // Used for remembering the millis() value in animations
#if RUN_DEMO
uint32_t prevTimeDemo = 0;      //  Used for remembering the millis() time in demo loop
uint8_t  timeDemo = DEMO_DELAY; // number of seconds left in this demo loop
#endif
void resetMatrix(void) {
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}
bool graphicMidline1(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Midline1 init");
    resetMatrix();
    bInit = false;
  }
  else
  {
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setRow(j, 3, 0xff);
      mx.setRow(j, 4, 0xff);
    }
  }

  return(bInit);
}

bool graphicMidline2(bool bInit)
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Midline2 init");
    resetMatrix();
    idx = 0;
    idOffs = 1;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < MIDLINE_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nML2 R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old lines
  for (uint8_t j=0; j<MAX_DEVICES; j++)
  {
    mx.setRow(j, idx, 0x00);
    mx.setRow(j, ROW_SIZE-1-idx, 0x00);
  }

  idx += idOffs;
  if ((idx == 0) || (idx == ROW_SIZE-1))
    idOffs = -idOffs;

  // turn on the new lines
  for (uint8_t j=0; j<MAX_DEVICES; j++)
  {
    mx.setRow(j, idx, 0xff);
    mx.setRow(j, ROW_SIZE-1-idx, 0xff);
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicScanner(bool bInit)
{
  const uint8_t width = 3;      // scanning bar width
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Scanner init");
    resetMatrix();
    idx = 0;
    idOffs = 1;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nS R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old lines
  for (uint8_t i=0; i<width; i++)
    mx.setColumn(idx+i, 0);

  idx += idOffs;
  if ((idx == 0) || (idx + width == mx.getColumnCount()))
    idOffs = -idOffs;

  // turn on the new lines
  for (uint8_t i=0; i<width; i++)
    mx.setColumn(idx+i, 0xff);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicRandom(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Random init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < RANDOM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i=0; i<mx.getColumnCount(); i++)
    mx.setColumn(i, (uint8_t)random(255));
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicScroller(bool bInit)
{
  const uint8_t   width = 3;     // width of the scroll bar
  const uint8_t   offset = mx.getColumnCount()/3;
  static uint8_t  idx = 0;      // counter

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Scroller init");
    resetMatrix();
    idx = 0;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nS I:", idx);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  mx.transform(MD_MAX72XX::TSL);

  mx.setColumn(0, idx>=0 && idx<width ? 0xff : 0);
  if (++idx == offset) idx = 0;

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicSpectrum1(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Spectrum1 init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SPECTRUM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i=0; i<MAX_DEVICES; i++)
  {
    uint8_t r = random(ROW_SIZE);
    uint8_t cd = 0;

    for (uint8_t j=0; j<r; j++)
      cd |= 1<<j;
    for (uint8_t j=1; j<COL_SIZE-1; j++)
      mx.setColumn(i, j, ~cd);
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicSpectrum2(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Spectrum2init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < SPECTRUM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i = 0; i<mx.getColumnCount(); i++)
  {
    uint8_t r = random(ROW_SIZE);
    uint8_t cd = 0;

    for (uint8_t j = 0; j<r; j++)
      cd |= 1 << j;

    mx.setColumn(i, ~cd);
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicHeartbeat(bool bInit)
{
  #define BASELINE_ROW  4

  static uint8_t  state;
  static uint8_t  r, c;
  static bool     bPoint;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Heartbeat init");
    resetMatrix();
    state = 0;
    r = BASELINE_ROW;
    c = mx.getColumnCount()-1;
    bPoint = true;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < HEARTBEAT_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nHB S:", state);
  PRINT(" R: ", r);
  PRINT(" C: ", c);
  PRINT(" P: ", bPoint);
  mx.setPoint(r, c, bPoint);

  switch (state)
  {
    case 0: // straight line from the right side
      if (c == mx.getColumnCount()/2 + COL_SIZE)
        state = 1;
      c--;
      break;

    case 1: // first stroke
      if (r != 0) { r--; c--; }
      else state = 2;
      break;

    case 2: // down stroke
      if (r != ROW_SIZE-1) { r++; c--; }
      else state = 3;
      break;

    case 3: // second up stroke
      if (r != BASELINE_ROW) { r--; c--; }
      else state = 4;
      break;

    case 4: // straight line to the left
      if (c == 0)
      {
        c = mx.getColumnCount()-1;
        bPoint = !bPoint;
        state = 0;
      }
      else c--;
      break;

    default:
      state = 0;
  }

  return(bInit);
}
bool graphicHearts(bool bInit)
{
#define NUM_HEARTS  ((MAX_DEVICES/2) +1)
  const uint8_t heartFull[] = { 0x1c, 0x3e, 0x7e, 0xfc };
  const uint8_t heartEmpty[] = { 0x1c, 0x22, 0x42, 0x84 };
  const uint8_t offset = mx.getColumnCount()/(NUM_HEARTS+1);
  const uint8_t dataSize = (sizeof(heartFull)/sizeof(heartFull[0]));

  static bool     bEmpty;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Hearts init");
    resetMatrix();
    bEmpty = true;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < HEARTS_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nH E:", bEmpty);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t h=1; h<=NUM_HEARTS; h++)
  {
    for (uint8_t i=0; i<dataSize; i++)
    {
      mx.setColumn((h*offset)-dataSize+i, bEmpty ? heartEmpty[i] : heartFull[i]);
      mx.setColumn((h*offset)+dataSize-i-1, bEmpty ? heartEmpty[i] : heartFull[i]);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  bEmpty = !bEmpty;

  return(bInit);
}

bool graphicEyes(bool bInit)
{
#define NUM_EYES  2
  const uint8_t eyeOpen[] = { 0x18, 0x3c, 0x66, 0x66 };
  const uint8_t eyeClose[] = { 0x18, 0x3c, 0x3c, 0x3c };
  const uint8_t offset = mx.getColumnCount()/(NUM_EYES+1);
  const uint8_t dataSize = (sizeof(eyeOpen)/sizeof(eyeOpen[0]));

  bool bOpen;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Eyes init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < EYES_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  bOpen = (random(1000) > 100);
  PRINT("\nH E:", bOpen);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t e=1; e<=NUM_EYES; e++)
  {
    for (uint8_t i=0; i<dataSize; i++)
    {
      mx.setColumn((e*offset)-dataSize+i, bOpen ? eyeOpen[i] : eyeClose[i]);
      mx.setColumn((e*offset)+dataSize-i-1, bOpen ? eyeOpen[i] : eyeClose[i]);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicBounceBall(bool bInit)
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- BounceBall init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nBB R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old ball
  mx.setColumn(idx, 0);
  mx.setColumn(idx+1, 0);

  idx += idOffs;
  if ((idx == 0) || (idx == mx.getColumnCount()-2))
    idOffs = -idOffs;

  // turn on the new lines
  mx.setColumn(idx, 0x18);
  mx.setColumn(idx+1, 0x18);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}
bool graphicWiper(bool bInit)
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Wiper init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < WIPER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nW R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.setColumn(idx, idOffs == 1 ? 0xff : 0);
  idx += idOffs;
  if ((idx == 0) || (idx == mx.getColumnCount()))
    idOffs = -idOffs;

  return(bInit);
}

bool graphicInvader(bool bInit)
{
  const uint8_t invader1[] = { 0x0e, 0x98, 0x7d, 0x36, 0x3c };
  const uint8_t invader2[] = { 0x70, 0x18, 0x7d, 0xb6, 0x3c };
  const uint8_t dataSize = (sizeof(invader1)/sizeof(invader1[0]));

  static int8_t idx;
  static bool   iType;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Invader init");
    resetMatrix();
    bInit = false;
    idx = -dataSize;
    iType = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < INVADER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nINV I:", idx);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();
  for (uint8_t i=0; i<dataSize; i++)
  {
    mx.setColumn(idx-dataSize+i, iType ? invader1[i] : invader2[i]);
    mx.setColumn(idx+dataSize-i-1, iType ? invader1[i] : invader2[i]);
  }
  idx++;
  if (idx == mx.getColumnCount()+(dataSize*2)) bInit = true;
  iType = !iType;
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicPacman(bool bInit)
{
  #define MAX_FRAMES  4   // number of animation frames
  #define PM_DATA_WIDTH  18
  const uint8_t pacman[MAX_FRAMES][PM_DATA_WIDTH] =  // ghost pursued by a pacman
  {
    { 0x3c, 0x7e, 0x7e, 0xff, 0xe7, 0xc3, 0x81, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xe7, 0x42, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xe7, 0x66, 0x24, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
  };

  static int16_t idx;        // display index (column)
  static uint8_t frame;      // current animation frame
  static uint8_t deltaFrame; // the animation frame offset for the next frame

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Pacman init");
    resetMatrix();
    bInit = false;
    idx = -1; //DATA_WIDTH;
    frame = 0;
    deltaFrame = 1;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < PACMAN_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nPAC I:", idx);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();

  // clear old graphic
  for (uint8_t i = 0; i<PM_DATA_WIDTH; i++)
    mx.setColumn(idx - PM_DATA_WIDTH + i, 0);
  // move reference column and draw new graphic
  idx++;
  for (uint8_t i = 0; i<PM_DATA_WIDTH; i++)
    mx.setColumn(idx - PM_DATA_WIDTH + i, pacman[frame][i]);

  // advance the animation frame
  frame += deltaFrame;
  if (frame == 0 || frame == MAX_FRAMES - 1)
    deltaFrame = -deltaFrame;

  // check if we are completed and set initialize for next time around
  if (idx == mx.getColumnCount() + PM_DATA_WIDTH) bInit = true;

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}
bool graphicSinewave(bool bInit)
{
  static uint8_t curWave = 0;
  static uint8_t idx;

  #define SW_DATA_WIDTH  11    // valid data count followed by up to 10 data points
  const uint8_t waves[][SW_DATA_WIDTH] =
  {
    {  9,   8,  6,   1,   6,  24,  96, 128,  96,  16,   0 },
    {  6,  12,  2,  12,  48,  64,  48,   0,   0,   0,   0 },
    { 10,  12,   2,   1,   2,  12,  48,  64, 128,  64, 48 },

  };
  const uint8_t WAVE_COUNT = sizeof(waves) / (SW_DATA_WIDTH * sizeof(uint8_t));

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Sinewave init");
    resetMatrix();
    bInit = false;
    idx = 1;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < SINE_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  mx.transform(MD_MAX72XX::TSL);
  mx.setColumn(0, waves[curWave][idx++]);
  if (idx > waves[curWave][0])
  {
    curWave = random(WAVE_COUNT);
    idx = 1;
  }
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);

  return(bInit);
}

bool scrollTextnormal(bool bInit, const char *pmsg, bool &textFinished)
// Callback function for data that is required for scrolling into the display
{
  static char   curMessage[BUF_SIZE];
  static char   *p = curMessage;
  static uint8_t  state = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t         colData;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Initializing ScrollText");
    resetMatrix();
    strcpy(curMessage, pmsg);
    state = 0;
    p = curMessage;
    textFinished = false;
    bInit = false;
  }

  // Is it time to scroll the text?
  if (millis()-prevTimeAnim < SCROLL_DELAY)
    return(bInit);

  // scroll the display
  mx.transform(MD_MAX72XX::TSL);  // scroll along
  prevTimeAnim = millis();        // starting point for next time

  // now run the finite state machine to control what we do
  PRINT("\nScroll FSM S:", state);
  switch (state)
  {
    case 0: // Load the next character from the font table
if(*p != '\0'){
      PRINTC("\nLoading ", *p);
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state = 1;
 }else{
          p = (char*)pmsg;
          state=0;
      }

    // !! deliberately fall through to next state to start displaying

    case 1: // display the next part of the character
      colData = cBuf[curLen++];
      mx.setColumn(0, colData);
      if (curLen == showLen)
      {
        showLen = ((*p != '\0') ? CHAR_SPACING : mx.getColumnCount()-1);
        curLen = 0;
        state = 2;
      }
      break;

    case 2: // display inter-character spacing (blank column) or scroll off the display
      mx.setColumn(0, 0);
      if (++curLen == showLen)
      {
  bInit = (*p == '\0');
        if(*p=='\0'){
          textFinished = true;
        }      
  state = 0;
      
      }
      break;

    default:
      state = 0;
  }
  return(bInit);
}


void animasi7() {
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t stripeWidth = 10;
  const unsigned long frameInterval = 100; // Interval waktu antara setiap frame (dalam milidetik)
  static unsigned long previousFrameTime = 0;
  static uint16_t col = 0;

  // State machine
  static enum { INIT, DRAW } state = INIT;

  switch (state) {
    case INIT:
      PRINTS("\nEach individually by row then col");
      mx.clear();
      state = DRAW;
      break;

    case DRAW:
      if (millis() - previousFrameTime >= frameInterval) {
        for (uint8_t row = 0; row < ROW_SIZE; row++) {
          if (col - row >= 0 && col - row < maxCol) {
            mx.setPoint(row, col - row, true);
          }
          if (col - row - stripeWidth >= 0 && col - row - stripeWidth < maxCol) {
            mx.setPoint(row, col - row - stripeWidth, false);
          }
        }
        previousFrameTime = millis();
        col++;

        if (col >= maxCol + ROW_SIZE + stripeWidth) {
            col=0;
            state = INIT;
        }
      }
      break;
  }
}

void animasi14() {
#define COM2_DELAY 30
  // Is it time to animate?
  if (millis() - prevTimeAnim < COM2_DELAY)
    return;
  prevTimeAnim = millis();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  // diagonally down the display R to L
  for (uint8_t i = 0; i < ROW_SIZE; i++) {
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, i, 0xff);
    }
    mx.update();
    delay(COM2_DELAY);
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, i, 0x00);
    }
  }
  // moving up the display on the R
  for (int8_t i = ROW_SIZE - 1; i >= 0; i--) {
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE - 1, 0xff);
    }
    mx.update();
    delay(COM2_DELAY);
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE - 1, 0x00);
    }
  }
  // diagonally up the display L to R
  for (uint8_t i = 0; i < ROW_SIZE; i++) {
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE - 1 - i, 0xff);
    }
    mx.update();
    delay(COM2_DELAY);
    for (uint8_t j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE - 1 - i, 0x00);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
void animasi15() {
#define COM3_DELAY 100
  if (millis() - prevTimeAnim < COM3_DELAY)
    return;
  prevTimeAnim = millis();
  uint8_t chkCols[][2] = { { 0x55, 0xaa }, { 0x33, 0xcc }, { 0x0f, 0xf0 }, { 0xff, 0x00 } };
  PRINTS("\nCheckboard");
  mx.clear();
  for (uint8_t pattern = 0; pattern < sizeof(chkCols) / sizeof(chkCols[0]); pattern++) {
    uint8_t col = 0;
    uint8_t idx = 0;
    uint8_t rep = 1 << pattern;

    while (col < mx.getColumnCount()) {
      for (uint8_t r = 0; r < rep; r++)
        mx.setColumn(col++, chkCols[pattern][idx]);  // use odd/even column masks
      idx++;
      if (idx > 1) idx = 0;
    }
    delay(COM3_DELAY);
  }
}
void animasi16() {
  static uint8_t rotationSpeed = 5;
  static bool increasingSpeed = true;

  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t stripeWidth = 2;
  const uint8_t minRotationSpeed = 5;
  const uint8_t maxRotationSpeed = 80;
  const uint16_t numFrames = 360 / rotationSpeed;

  mx.clear();

  for (uint16_t frame = 0; frame < numFrames; frame++) {
    float radian = radians(frame * rotationSpeed);

    for (uint8_t row = 0; row < ROW_SIZE; row++) {
      for (uint16_t col = 0; col < maxCol; col++) {
        float centerX = maxCol / 2.0;
        float centerY = ROW_SIZE / 2.0;
        float x = col - centerX;
        float y = row - centerY;

        float rotatedX = x * cos(radian) - y * sin(radian);
        float rotatedY = x * sin(radian) + y * cos(radian);

        if (abs(rotatedX) < stripeWidth / 2) {
          mx.setPoint(row, col, true);
        } else {
          mx.setPoint(row, col, false);
        }
      }
    }

    delay(30);
    mx.clear();
  }

  if (increasingSpeed) {
    rotationSpeed = rotationSpeed + 10;
    if (rotationSpeed >= maxRotationSpeed) {
      increasingSpeed = false;
    }
  } else {
    rotationSpeed = rotationSpeed - 10;
    if (rotationSpeed <= minRotationSpeed) {
      increasingSpeed = true;
    }
  }
}
void animasi17() {
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t boxWidth = 2;
  const uint8_t boxHeight = 8;
  const uint8_t animationSpeed = 30;

  uint32_t currentTime = millis();

  // Pastikan untuk menambahkan prevTimeAnim sebagai variabel statis
  static uint32_t prevTimeAnim = 0;

  // Periksa waktu sejak animasi terakhir dieksekusi
  if (currentTime - prevTimeAnim < animationSpeed) {
    // Belum saatnya untuk menjalankan animasi lagi
    return;
  }
  prevTimeAnim = currentTime;

  // Cetak pesan debug
  PRINTS("\nBox Animation");

  // Hapus tampilan sebelum menggambar kotak
  mx.clear();

  // Hitung frame saat ini
  uint16_t currentFrame = (currentTime / animationSpeed) % (maxCol - boxWidth);

  // Gambar kedua kotak dalam satu loop
  for (uint8_t row = 0; row < boxHeight; row++) {
    for (uint16_t col = currentFrame; col < currentFrame + boxWidth; col++) {
      if (col >= 0 && col < maxCol && row < ROW_SIZE) {
        // Gambar kotak kiri
        mx.setPoint(row, col, true);

        // Gambar kotak kanan
        mx.setPoint(row, maxCol - col - 1, true);
      }
    }
  }
}

void animasi18() {
#define COM6_DELAY 10
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t pyramidHeight = 3;
  const float zoomSpeed = 0.1;

  PRINTS("\nZooming Pyramid Animation");
  

  float scaleFactor = 2.0;
  bool zoomingIn = true;

  // Set the number of iterations for the loop
  const int numIterations = 100;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update scale factor
    if (zoomingIn) {
      scaleFactor += zoomSpeed;
      if (scaleFactor >= 8) {
        zoomingIn = false;
      }
    } else {
      scaleFactor -= zoomSpeed;
      if (scaleFactor <= 1.0) {
        zoomingIn = true;
      }
    }

    // Draw the pyramid at the center with the scaled factor
    int16_t scaledPyramidHeight = int(pyramidHeight * scaleFactor);
    int16_t pyramidTop = ROW_SIZE / 2 - scaledPyramidHeight / 2;
    for (int8_t i = 0; i < scaledPyramidHeight; i++) {
      int16_t row = pyramidTop + i;
      int16_t startCol = maxCol / 2 - i;
      int16_t endCol = maxCol / 2 + i;
      for (int16_t col = startCol; col <= endCol; col++) {
        if (row >= 0 && row < ROW_SIZE && col >= 0 && col < maxCol) {
          mx.setPoint(row, col, true);
        }
      }
    }

    // Delay for animation
    delay(COM6_DELAY);
  }
}
void animasi19() {
#define COM5_DELAY 15
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t waveWidth = 5;
  const uint8_t waveAmplitude = 5;
  const float waveFrequency = 0.1;

  PRINTS("\nSynchronized Thick Wave Animation");
  mx.clear();

  float wavePhase = 0;

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update wave phase
    wavePhase += waveFrequency;

    // Draw the waves at the updated positions
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      int16_t col1 = int(maxCol / 4 + waveAmplitude * sin(wavePhase + row * waveFrequency));
      int16_t col2 = int(maxCol * 3 / 4 + waveAmplitude * sin(wavePhase + row * waveFrequency));

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t col1Thick = col1 + xOffset;
        int16_t col2Thick = col2 + xOffset;

        if (col1Thick >= 0 && col1Thick < maxCol) {
          mx.setPoint(row, col1Thick, true);
        }
        if (col2Thick >= 0 && col2Thick < maxCol) {
          mx.setPoint(row, col2Thick, true);
        }
      }
    }

    // Delay for animation
    delay(COM5_DELAY);
  }
}
void animasi20() {
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t crossSize = 4;
  const uint8_t rotationSpeed = 7;
  const uint16_t numFrames = 360 / rotationSpeed;  // Calculate the number of frames

  PRINTS("\nRotating Cross Animation");
  mx.clear();

  for (uint16_t frame = 0; frame < numFrames; frame++) {
    float radian = radians(frame * rotationSpeed);

    for (uint8_t row = 0; row < ROW_SIZE; row++) {
      for (uint16_t col = 0; col < maxCol; col++) {
        // Calculate the distance from the center of rotation
        float centerX = maxCol / 2.0;
        float centerY = ROW_SIZE / 2.0;
        float x = col - centerX;
        float y = row - centerY;

        // Rotate the point around the center of rotation
        float rotatedX = x * cos(radian) - y * sin(radian);
        float rotatedY = x * sin(radian) + y * cos(radian);

        // Set points for the rotating cross
        if (abs(rotatedX) < crossSize / 2 || abs(rotatedY) < crossSize / 2) {
          mx.setPoint(row, col, true);
        } else {
          mx.setPoint(row, col, false);
        }
      }
    }

    delay(20);
    mx.clear();
  }
}
void bullseye()
// Demonstrate the use of buffer based repeated patterns
// across all devices.
{
  PRINTS("\nBullseye");
  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (uint8_t n=0; n<3; n++)
  {
    byte  b = 0xff;
    int   i = 0;

    while (b != 0x00)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(3*30);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      bitClear(b, i);
      bitClear(b, 7-i);
      i++;
    }

    while (b != 0xff)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(3*30);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      i--;
      bitSet(b, i);
      bitSet(b, 7-i);
    }
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
void spiral()
// setPoint() used to draw a spiral across the whole display
{
  PRINTS("\nSpiral in");
  int  rmin = 0, rmax = ROW_SIZE-1;
  int  cmin = 0, cmax = (COL_SIZE*MAX_DEVICES)-1;

  mx.clear();
  while ((rmax > rmin) && (cmax > cmin))
  {
    // do row
    for (int i=cmin; i<=cmax; i++)
    {
      mx.setPoint(rmin, i, true);
      delay(100/MAX_DEVICES);
    }
    rmin++;

    // do column
    for (uint8_t i=rmin; i<=rmax; i++)
    {
      mx.setPoint(i, cmax, true);
      delay(100/MAX_DEVICES);
    }
    cmax--;

    // do row
    for (int i=cmax; i>=cmin; i--)
    {
      mx.setPoint(rmax, i, true);
      delay(100/MAX_DEVICES);
    }
    rmax--;

    // do column
    for (uint8_t i=rmax; i>=rmin; i--)
    {
      mx.setPoint(i, cmin, true);
      delay(100/MAX_DEVICES);
    }
    cmin++;
  }
}
void blinking()
// Uses the test function of the MAX72xx to blink the display on and off.
{
  int  nDelay = 1000;

  PRINTS("\nBlinking");
  mx.clear();

  while (nDelay > 0)
  {
    mx.control(MD_MAX72XX::TEST, MD_MAX72XX::ON);
    delay(nDelay);
    mx.control(MD_MAX72XX::TEST, MD_MAX72XX::OFF);
    delay(nDelay);

    nDelay -= 200;
  }
}

void rem1(){
      i = 0;
      //delay(50);
      mx.clear();
      delay(60);
      for(int i=0;i<8;i++) {
        mx.setRow(2, i, stop_s[i]);
        mx.setRow(1, i, stop_t[i]);
        mx.setRow(0, i, stop_op[i]);
      };
      
      delay(60);
      mx.clear();
      delay(60);
      
      for(int i=0;i<8;i++) {
        mx.setRow(2, i, stop_s[i]);
        mx.setRow(1, i, stop_t[i]);
        mx.setRow(0, i, stop_op[i]);
      };
      delay(60);
      mx.clear();
      delay(60);

      for(int i=0;i<8;i++) {
        mx.setRow(2, i, stop_s[i]);
        mx.setRow(1, i, stop_t[i]);
        mx.setRow(0, i, stop_op[i]);
      };

      delay(60);
      mx.clear();
}
void rem2()
// Demonstrates animation of a diagonal stripe moving across the display
// with points plotted outside the display region ignored.
{
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t ballSize = 8;  // Increased size for a thicker ball
  const uint8_t initialSpeed = 3;
  const uint8_t speedIncreaseLimit = 10;  // Increase speed only 7 times

  PRINTS("\nControlled Bouncing Thick Ball Animation");
  mx.clear();

  float ballX = maxCol / 2.0;
  float ballY = ROW_SIZE / 2.0;
  float speed = initialSpeed;

  int8_t xDirection = 1;          // 1 for moving right, -1 for moving left
  int8_t speedIncreaseCount = 0;  // Counter for speed increase

  while (speedIncreaseCount < speedIncreaseLimit) {
    // Clear previous ball position
    mx.clear();

    // Update ball position
    ballX += xDirection * speed;

    // Bounce if the ball hits the edge
    if (ballX < 0) {
      ballX = 0;
      xDirection = 1;
      speedIncreaseCount++;
      speed += 0.5;
    } else if (ballX >= maxCol) {
      ballX = maxCol - 1;
      xDirection = -1;
      speedIncreaseCount++;
      speed += 0.5;
    }

    // Draw the thick ball at the updated position
    for (int8_t yOffset = -ballSize / 2; yOffset <= ballSize / 2; yOffset++) {
      for (int8_t xOffset = -ballSize / 2; xOffset <= ballSize / 2; xOffset++) {
        int16_t col = ballX + xOffset;
        int16_t row = ballY + yOffset;
        if (col >= 0 && col < maxCol && row >= 0 && row < ROW_SIZE) {
          mx.setPoint(row, col, true);
        }
      }
    }

    // Delay for animation
    delay(25);
  }

  // Clear the display after the animation ends
  mx.clear();
}
void kanan1()
// Demonstrates the use of transform() to move bitmaps on the display

// In this case a user defined bitmap is created and animated.
{
  mx.clear();
  uint8_t arrow[COL_SIZE] =
{
  0b00000000,
  0b00011000,
  0b00111100,
  0b01111110,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00000000
};

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    // MD_MAX72XX::TFLR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TRC,
    // MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    // MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    // MD_MAX72XX::TFUD,
    // MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    // MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    // MD_MAX72XX::TINV,
    // MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    // MD_MAX72XX::TINV
  };

  PRINTS("\nTransformation1");
  mx.clear();

  // use the arrow bitmap
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t j=0; j<mx.getDeviceCount(); j++)
    mx.setBuffer(((j+1)*COL_SIZE)-1, COL_SIZE, arrow);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(50);

  // run through the transformations
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  for (uint8_t i = 0; i < (sizeof(t) / sizeof(t[0])) * 3; i++)  // Mengulangi transformasi 3 kali
{
  mx.transform(t[i % (sizeof(t) / sizeof(t[0]))]);  // Menggunakan sirkular indexing untuk mengulang daftar transformasi
  delay(50);
}
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);
  mx.clear();
}
void kiri1()
// Demonstrates the use of transform() to move bitmaps on the display
// In this case a user defined bitmap is created and animated.
{
  mx.clear();
  uint8_t arrow[COL_SIZE] ={
 0b00000000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
  };

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TFLR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    // MD_MAX72XX::TRC,
    // MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    // MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    // MD_MAX72XX::TFUD,
    // MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    // MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    // MD_MAX72XX::TINV,
    // MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    // MD_MAX72XX::TINV
  };

  PRINTS("\nTransformation1");
  mx.clear();

  // use the arrow bitmap
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t j=0; j<mx.getDeviceCount(); j++)
    mx.setBuffer(((j+1)*COL_SIZE)-1, COL_SIZE, arrow);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(50);

  // run through the transformations
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
   for (uint8_t i = 0; i < (sizeof(t) / sizeof(t[0])) * 3; i++)  // Mengulangi transformasi 3 kali
{
  mx.transform(t[i % (sizeof(t) / sizeof(t[0]))]);  // Menggunakan sirkular indexing untuk mengulang daftar transformasi
  delay(50);
}
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);
  mx.clear();
}

void rem3(uint8_t modStart, uint8_t modEnd, char *pMsg)
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
  uint8_t state = 0;
  uint8_t curLen;
  uint16_t showLen;
  uint8_t cBuf[8];
  int16_t col = ((modEnd + 1) * COL_SIZE) - 1;
  int16_t msgWidth = col + 1;

   int16_t textLen = 0;
  char *p = pMsg;
  while (*p != '\0') {
     uint8_t charWidth = mx.getChar(*p, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
    if (charWidth  > 0) {
      textLen += charWidth  + 1;
      p++;
    }
  }
  textLen -= 1; // Remove trailing spacing

  int16_t startPos = (msgWidth - textLen) / 2;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();
  col = msgWidth - 1;
  do  // finite state machine to print the characters in the space available
  {
    switch (state) {
      case 0:  // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0') {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1:  // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen) {
          showLen = 1;
          state = 2;
        }
        break;

      case 2:  // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3:  // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;  // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void rem4()
// Uses the test function of the MAX72xx to blink the display on and off.
{
  int  nDelay = 100;

  PRINTS("\nBlinking");
  mx.clear();

  while (nDelay > 0)
  {
    mx.control(MD_MAX72XX::TEST, MD_MAX72XX::ON);
    delay(nDelay);
    mx.control(MD_MAX72XX::TEST, MD_MAX72XX::OFF);
    delay(nDelay);
    nDelay -= 50;
  }
}

void customWaveAnimation() {
#define COM5_DELAY 15
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t waveWidth = 5;
  const uint8_t waveAmplitude = 5;
  const float waveFrequency = 0.1;

  PRINTS("\nCustom Wave Animation");
  mx.clear();

  float wavePhase = 0;

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update wave phase
    wavePhase += waveFrequency;

    // Draw the waves at the updated positions with a custom shape
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      int16_t col1 = int(maxCol / 4 + waveAmplitude * cos(wavePhase + row * waveFrequency));
      int16_t col2 = int(maxCol * 3 / 4 + waveAmplitude * sin(wavePhase + row * waveFrequency));

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t col1Thick = col1 + xOffset;
        int16_t col2Thick = col2 + xOffset;

        if (col1Thick >= 0 && col1Thick < maxCol) {
          mx.setPoint(row, col1Thick, true);
        }
        if (col2Thick >= 0 && col2Thick < maxCol) {
          mx.setPoint(row, col2Thick, true);
        }
      }
    }

    // Delay for animation
    delay(20);
  }
}
void alternateWaveAnimation() {
#define COM5_DELAY 15
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t waveWidth = 6;
  const uint8_t waveAmplitude = 4;
  const float waveFrequency = 0.15;

  PRINTS("\nAlternate Wave Animation");
  mx.clear();

  float wavePhase1 = 0;
  float wavePhase2 = PI;  // Offset the second wave

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update wave phases
    wavePhase1 += waveFrequency;
    wavePhase2 += waveFrequency;

    // Draw the alternating waves
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      int16_t col1 = int(maxCol / 2 + waveAmplitude * sin(wavePhase1 + row * waveFrequency));
      int16_t col2 = int(maxCol / 2 + waveAmplitude * sin(wavePhase2 + row * waveFrequency));

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t col1Thick = col1 + xOffset;
        int16_t col2Thick = col2 + xOffset;

        if (col1Thick >= 0 && col1Thick < maxCol) {
          mx.setPoint(row, col1Thick, true);
        }
        if (col2Thick >= 0 && col2Thick < maxCol) {
          mx.setPoint(row, col2Thick, true);
        }
      }
    }

    // Delay for animation
    delay(20);
  }
}
void alternateWaveAnimation2() {
#define COM5_DELAY 15
  const uint16_t maxCol = MAX_DEVICES * COL_SIZE;
  const uint8_t waveWidth = 6;
  const uint8_t waveAmplitude = 4;
  const float waveFrequency = 0.15;

  PRINTS("\nAlternate Wave Animation");
  mx.clear();

  float wavePhase1 = 0;
  float wavePhase2 = PI;  // Offset the second wave

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update wave phases
    wavePhase1 += waveFrequency;
    wavePhase2 += waveFrequency;

    // Draw the alternating waves
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      float waveValue1 = waveAmplitude * sin(wavePhase1 + row * waveFrequency);
      float waveValue2 = waveAmplitude * sin(wavePhase2 + row * waveFrequency);

      int16_t col1 = int(maxCol / 2 + waveValue1 * COL_SIZE / 2);
      int16_t col2 = int(maxCol / 2 + waveValue2 * COL_SIZE / 2);

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t col1Thick = col1 + xOffset;
        int16_t col2Thick = col2 + xOffset;

        if (col1Thick >= 0 && col1Thick < maxCol) {
          mx.setPoint(row, col1Thick, true);
        }
        if (col2Thick >= 0 && col2Thick < maxCol) {
          mx.setPoint(row, col2Thick, true);
        }
      }
    }

    // Delay for animation
    delay(COM5_DELAY);
  }
}
void oppositeWaveAnimation() {
  const uint16_t maxCol = MAX_DEVICES * COL_SIZE;
  const uint8_t waveWidth = 6;
  const uint8_t waveAmplitude = 4;
  const float waveFrequency = 0.15;

  PRINTS("\nOpposite Wave Animation");
  mx.clear();

  float wavePhase1 = 0;
  float wavePhase2 = PI;  // Offset the second wave

  // Set the number of iterations for the loop
  const int numIterations = 40;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Clear previous frame
    mx.clear();

    // Update wave phases
    wavePhase1 += waveFrequency;
    wavePhase2 += waveFrequency;

    // Draw the opposite waves
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      float waveValue1 = waveAmplitude * sin(wavePhase1 + row * waveFrequency);
      float waveValue2 = waveAmplitude * sin(wavePhase2 - row * waveFrequency);

      int16_t col1 = int(maxCol / 2 + waveValue1 * COL_SIZE / 2);
      int16_t col2 = int(maxCol / 2 + waveValue2 * COL_SIZE / 2);

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t col1Thick = col1 + xOffset;
        int16_t col2Thick = col2 + xOffset;

        if (col1Thick >= 0 && col1Thick < maxCol) {
          mx.setPoint(row, col1Thick, true);
        }
        if (col2Thick >= 0 && col2Thick < maxCol) {
          mx.setPoint(row, col2Thick, true);
        }
      }
    }

    // Update display
    mx.update();
    delay(20);
  }
}

void waveAnimation() {
  const uint16_t maxCol = MAX_DEVICES * COL_SIZE;
  const uint8_t waveWidth = 5;
  const uint8_t waveAmplitude = 4;
  const float waveFrequency = 0.1;

  PRINTS("\nWave Animation");
  mx.clear();

  float wavePhase = 0;

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    // Update wave phase
    wavePhase += waveFrequency;

    // Clear previous frame
    mx.clear();

    // Draw the wave moving up and down
    for (int16_t row = 0; row < ROW_SIZE; row++) {
      float waveValue = waveAmplitude * sin(wavePhase + row * waveFrequency);
      int16_t col = int(maxCol / 2 + waveValue * COL_SIZE / 2);

      // Draw multiple columns for thickness
      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t colThick = col + xOffset;

        if (colThick >= 0 && colThick < maxCol) {
          mx.setPoint(row, colThick, true);
        }
      }
    }

    // Update display
    mx.update();
    delay(20);
  }
}

void circleWaveAnimation() {
  const uint16_t maxCol = MAX_DEVICES * COL_SIZE;
  const uint8_t waveWidth = 7;
  const uint8_t waveAmplitude =4;
  const float waveFrequency = 0.1;

  mx.clear();

  float wavePhase = 0;

  // Set the number of iterations for the loop
  const int numIterations = 60;  // Change this to the desired number of iterations

  for (int iteration = 0; iteration < numIterations; iteration++) {
    wavePhase += waveFrequency;

    mx.clear();

    for (int16_t row = 0; row < ROW_SIZE; row++) {
      int16_t col = int(maxCol / 2 + waveAmplitude * sin(wavePhase + row * waveFrequency));

      for (int8_t xOffset = -waveWidth / 2; xOffset <= waveWidth / 2; xOffset++) {
        int16_t colThick = col + xOffset;

        if (colThick >= 0 && colThick < maxCol) {
          mx.setPoint(row, colThick, true);
        }
      }
    }

    mx.update();
    delay(20);
  }
}
