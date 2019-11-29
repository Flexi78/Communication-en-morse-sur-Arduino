bool isLightDetected;             //Détermine si du bruit a été détécté
int lightIntensityMesure;         //Intensité du bruit
unsigned long lightTimeInterval;  //Durée du bruit
unsigned long pauseTimeStart;     //Début du silence
unsigned long pauseTimeInterval;  //Durée du silence
bool pauseDetected;               //Détermine si du silence a été détécté
String morseInputDetected;
String charDetected[3];
int charSize;
bool aboutToQuit;

static String tabMorse[] = {"._!!","_...", "_._.", "_..!", ".!!!", ".._.", "__.!", "....",
                             "..!!", ".___", "_._!", "._..", "__!!", "_.!!", "___!", ".__.", "__._",
                             "._.!", "...!", "_!!!", ".._!", "..._", ".__!", "_.._", "_.__", "__..", "!!!!"
                             };

//  Fonction Start
void setup()
{
  Serial.begin(9600);
  isLightDetected = false;
  pauseDetected = false;
  charSize = 0;
  aboutToQuit = false;
}


//  Fonction Update
void loop()
{
  lightIntensityMesure=analogRead(A0);

  //  Début de détection du bruit
  if (lightIntensityMesure > 1000 && isLightDetected == false)
  {
    if (pauseTimeInterval > 900)
    {
      morseInputDetected = "!";
      CheckCharTable(lightTimeInterval);
      pauseTimeInterval = 0;
      pauseDetected = false;
    }
     
    lightTimeInterval = millis();
    isLightDetected = true;
  }

  //  Fin de détection du bruit
  if (lightIntensityMesure <= 1000 && isLightDetected == true)
  {
    lightTimeInterval = millis() - lightTimeInterval;
    pauseTimeStart = millis();
    morseInputDetected = MorseTransform (lightTimeInterval);
    CheckCharTable(lightTimeInterval);
    pauseDetected = true;
    isLightDetected = false;
  }

  //  Calcul du silence
  if(pauseDetected == true)
  {
    pauseTimeInterval = millis() - pauseTimeStart;

    if (pauseTimeInterval > 1000 )
    {
      morseInputDetected = "!";
      CheckCharTable(lightTimeInterval);
      pauseTimeInterval = 0;
      pauseTimeStart = millis();
    }
  }
}


//  Transformation du bruit en caractère morse
String MorseTransform (int timeInterval)
{
  String identifiedCharacter;
  
  if (timeInterval > 400)
  {
    identifiedCharacter = "_";
  }
  
  if (timeInterval <= 400)
  {
    identifiedCharacter = ".";
  }
  
  return identifiedCharacter;
}


//
void CheckCharTable(int timeInterval)
{
  if(charSize < 4)
  {
    charDetected[charSize] = morseInputDetected;
    charSize++;
  }
  
  if(charSize == 4)
  {
    morseincoming(charDetected);   
    charSize = 0;
  }
}


//
void morseincoming(String charDetectedTable[])
{  
  String myMessage;
  for(int k = 0; k < 4; k++)
  {
    myMessage += charDetectedTable[k];
  }
  if(myMessage == "!!!!")
  {
    if(aboutToQuit == true)
      {
        pauseDetected = false;
        aboutToQuit = false;
      }
      
      Serial.print(" ");
      aboutToQuit = true;
  }
  else
  {
    for(int i = 0; i < 26; i++)
    {
      if(myMessage == tabMorse[i])
      {
        Serial.print(char('a' + i));
        aboutToQuit = false;
        break;
      }
    }
  }
}
