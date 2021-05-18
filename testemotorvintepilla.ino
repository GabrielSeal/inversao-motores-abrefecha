int motord = 7;
int motores = 8;
void giraesquerda() 
{
  digitalWrite (motord,HIGH);
  digitalWrite (motores, LOW); 
}
void giradireita()
{
  digitalWrite(motord, LOW);
  digitalWrite(motores, HIGH);

}
void setup() {
  // put your setup code here, to run once:
pinMode (motord, OUTPUT);
pinMode (motores, OUTPUT);
digitalWrite (motord,LOW);
digitalWrite (motores,LOW);


}

void loop() {
  
giraesquerda();
delay(1000);
giradireita();
delay(1000);
}
