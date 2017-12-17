void addChar(char * s, char c) {
  int n = strlen(s);
  s[n] = c;
  s[n+1] = '\0';
}

void readValue() {
  char s[50];
  strcpy(s,"read_char_");

  char c = '@';
  while(c != 'X' && c != 'Y') c = Serial.read();
  addChar(s, c);
  strcat(s,"\n");
  Serial.print(s);
}

int n;

void setup() {
 Serial.begin(9600);
 n = 200;
}

void loop() {
  char message[50];
  strcpy(message, "mmm_");
  char s[20];
  itoa(n,s,10);
  strcat(message,s);
  strcat(message,"\n");
  Serial.print(message);
  readValue();
  delay(200);
  n++;
}
