const int NUM_OF_MOTORS = 4;

int motor1Velo, motor2Velo, motor3Velo, motor4Velo;
int motor1Dir, motor2Dir, motor3Dir, motor4Dir;
String data;
String lastData;

int *velocityArray[] = {&motor1Velo, &motor2Velo, &motor3Velo, &motor4Velo} ;
int *directionArray[] = {&motor1Dir, &motor2Dir, &motor3Dir, &motor4Dir};

void generateRandVelocity(int *velos[], int arraySize);                    // her motor icin rastgele hiz atar (0,255 arasi)
void generateRandDirection(int *directions[], int arraySize);              // her motor icin rastgele yon atar (0 ve 1)
String createFinalString(int* velos[], int *directions[], int arraySize);  // 18 karakterlik stringi uretir
String addZeros(String velocity);                                          // uc basamakli olmayan motor hizlarinin basina '0' ekler


void setup() {
  
  int seedValue = analogRead(0); 
  randomSeed(seedValue); //rastgeleligi biraz daha artirmak icin (program yeniden baslatildiginda)
  Serial.begin(9600);
}

void loop() {
  generateRandVelocity(velocityArray, NUM_OF_MOTORS);
  generateRandDirection(directionArray, NUM_OF_MOTORS);
  while (true) {
      data = createFinalString(velocityArray,directionArray, NUM_OF_MOTORS);
          if (data != lastData){
              break;
          }
       }
       
  Serial.println(data);
  delay(2000);
}

void generateRandVelocity(int *velos[], int arraySize)
{
    for (int i=0; i < arraySize; i++){
        *velos[i] = int(random(0,256));
    }
}

void generateRandDirection(int *directions[], int arraySize)
{
    for (int i=0; i < arraySize; i++){
        *directions[i] = int(random(0,2));
    }
}

String createFinalString(int* velos[], int *directions[], int arraySize)
{
    String output = "S";
     
    for (int i=0; i < arraySize; i++)
    {
        String velocity = String(*velos[i]);
        output = output + *directions[i] + addZeros(velocity);
    }
    output += "F";
    return output;
}

String addZeros(String velocity)
{
    while (velocity.length() < 3)
    {
      velocity = "0" + velocity;
    }
    return velocity;
 }
