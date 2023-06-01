//bibliotecas antes que eu esqueça 

const int pinMotorR_F=4, // IN1
          pinMotorR_B=3, // IN2
          pinMotorL_F=9, // IN3
          pinMotorL_B=8, // IN4
          pinUltraFTrig=11,
          pinUltraFEcho=10,

          pinUltraFTrig=13,
          pinUltraFEcho=12,
          
          pinLdrR= A0,
          pinLdrL = A1; //pinos

const int pwmSpeed=130;
float duration, distance;  //variaveis do ultrassom


enum estados{
    Frente,
    RodandoR,
    RodandoL
};
estados estadoAtual= Frente;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinMotorR_F, OUTPUT);
  pinMode(pinMotorR_B, OUTPUT);

  pinMode(pinMotorL_F, OUTPUT);
  pinMode(pinMotorL_B, OUTPUT);
  
  pinMode(pinUltraTrig, OUTPUT);
  pinMode(pinUltraEcho, INPUT); //pinagem
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(estadoAtual) //proto FSM
  {
    case Frente:
      analogWrite(pinMotorR_F,pwmSpeed);
      analogWrite(pinMotorL_F,pwmSpeed);
      break;
    case RodandoR:
      analogWrite(pinMotorR_F,pwmSpeed);
      analogWrite(pinMotorR_B,0);
      analogWrite(pinMotorL_B,pwmSpeed);
      analogWrite(pinMotorL_F,0);
      delay(500);
      analogWrite(pinMotorR_F,0);
      analogWrite(pinMotorL_B,0);
      estadoAtual= Frente;
      break;
    case RodandoL:
      analogWrite(pinMotorL_F,pwmSpeed);
      analogWrite(pinMotorR_B,pwmSpeed);
      delay(500);
      analogWrite(pinMotorR_F,0);
      analogWrite(pinMotorL_B,0);
      estadoAtual= Frente;
      break;
  }

  	digitalWrite(pinUltraTrig, LOW);  
    delayMicroseconds(2);  
    digitalWrite(pinUltraTrig, HIGH);  
    delayMicroseconds(10);  
    digitalWrite(pinUltraTrig, LOW); 
    duration = pulseIn(pinUltraEcho, HIGH);
    distance = (duration*.0343)/2;
    
    estadoAtual = distance < 5 ? RodandoR: Frente; //vira pra direita se encontrar um obj a 5 cm de distancia

}




