const byte numeral[10] = { //catodo comun
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};
//definicion de pines del arduino para los codificadores
const int segmentosPins[8] = {3, 4, 5, 6}; //D,C,B,A
const int digitosPins[4] = {13, 12, 11, 10}; //pines para encender cada display
//variales de conteo
int contador = 0;
int contador1 = 0;
int minutoDecenas = 0;
int minutosUnidades = 0;
int segundosDecenas = 0;
int segundosUnidades = 0;
int button = A0;
int button2 = A1;
int reset = A2;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
void setup() {
  for (int i = 0; i < 4; i++) { //para los segmentos
    pinMode(segmentosPins[i], OUTPUT);
    pinMode(digitosPins[i], OUTPUT);
  }
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  pinMode(reset, INPUT);
}

void verificar() {
  if (minutoDecenas >= 60) {
    minutoDecenas = 0;
  }
  if (minutosUnidades >= 60) {
    minutosUnidades = 0;
  }
  if (segundosDecenas >= 60) {
    segundosDecenas = 0;
  }
  if (segundosUnidades >= 60) {
    segundosUnidades = 0;
  }
}
//Metodo para contar
void aumentar() {
  if (digitalRead(button) == 0) {
    while (digitalRead(button) == 0) {
      visuailiza2(minutoDecenas, minutosUnidades, segundosDecenas, segundosUnidades);
    }
    contador1++;
    if (contador1 == 60) {
      contador1 = 0;
    }
  }
}
//metodo btn
void disminuir() {
  if (digitalRead(button2) == 0) {
    while (digitalRead(button2) == 0) {
      visuailiza2(minutoDecenas, minutosUnidades, segundosDecenas, segundosUnidades);
    }
    contador1--;
    if (contador1 == -1) {
      contador1 = 59;

    }
  }


}
//metodo btn reiniciar
void reiniciar() {
  // reinicio
  if (digitalRead(reset) == 0) {
    do {
      visuailiza2(minutoDecenas, minutosUnidades, segundosDecenas, segundosUnidades);
    } while (digitalRead(reset) == 0);
    contador = 0;
    contador1 = 0;
  }
  visuailiza2(minutoDecenas, minutosUnidades, segundosDecenas, segundosUnidades);
}
//metodo Visualizar
void visuailiza2(int dec, int uni, int dec1, int uni1) {
  const int NumeroCompleto[4] = {numeral[minutoDecenas], numeral[minutosUnidades], numeral[segundosDecenas], numeral[segundosUnidades]};
  for (int cifra = 0; cifra < 4; cifra++) {
    for (int i = 0; i < 4; i++) {
      int segmentos = segmentosPins[i];
      digitalWrite(segmentos, bitRead(NumeroCompleto[cifra], i));
    }
    digitalWrite(digitosPins[cifra], HIGH);
    delay(1);
    digitalWrite(digitosPins[cifra], LOW);
  }
}
//Metodo para sepaar cifras
void SepararCifras(int num, int num2) {
  //85
  segundosDecenas = num / 10; //extrae decenas
  minutoDecenas = num2 / 10;
  //decenas=8
  segundosUnidades = num - segundosDecenas * 10;
  minutosUnidades = num2 - minutoDecenas * 10; //extrae unidades
  //unidades=5
}
void aumentarTiempo() {
  contador++;
  if (contador == 60) {
    contador = 0;
    contador1++;
  }
  if (contador1 == 60) {
    contador = 0;
    contador1 = 0;
  }
}
void loop() {
  tiempo2 = millis();
  if (tiempo2 > (tiempo1 + 1000)) { //Si ha pasado 1 segundo ejecuta el IF
    tiempo1 = millis(); //Actualiza el tiempo actual
    SepararCifras(contador, contador1);
    aumentarTiempo();
  }
  aumentar();
  disminuir();
  reiniciar();
  visuailiza2(minutoDecenas, minutosUnidades, segundosDecenas, segundosUnidades);
}
