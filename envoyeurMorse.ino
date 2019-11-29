int laser = 1;
String texte[] = "bonjour";
char texteAenvoyer[4];
static String tabAlphabet[] = {"a","b", "c", "d", "e", "f", "g", "h",
                                "i", "j", "k", "l", "m", "n", "o", "p", "q",
                                 "r", "s", "t", "u", "v", "w", "x", "y", "z", " "
                             };
static String tabMorse[] = {".-!!","-...", "-.-.", "-..!", ".!!!", "..-.", "--.!", "....",
                             "..!!", ".---", "-.-!", ".-..!", "--!!", "-.!!", "---!", ".--.", "--.-",
                             ".-.!", "...!", "-!!!!", "..-!", "...-", ".--!", "-..-", "-.--", "--..", "!!!!"
                             };

void setup() {
  // put your setup code here, to run once:
 pinMode(laser,OUTPUT);
 digitalWrite(laser,LOW);
 delay(6000);
}

void loop() {
  // put your main code here, to run repeatedly:
int i; 
String texteMorse;
int taille=((sizeof(texte))/(sizeof(char)));

for (i=0;i<taille;i++)
{
  texteMorse=morseOutput(texte[i]);
  texteMorse.toCharArray(texteAenvoyer[i],sizeof(texteAenvoyer));
  envoi(texteAenvoyer,4);

}

//envoi(texteMorse,taille*4);

}



void envoi(char param[],int taille)
{
  int i;
  for(i=0;i<taille;i++)//(sizeof(param))
  {
    if(param[i]=='.')
    {
       digitalWrite(laser,HIGH);
       Serial.print('.');
       delay(300);
       digitalWrite(laser,LOW);
       delay(200);
    }
    if(param[i]=='_')
    {
       digitalWrite(laser,HIGH);
       Serial.print('_');
       delay(700);
       digitalWrite(laser,LOW);
       delay(200);
    }
    if(param[i]=='!')
    {
       digitalWrite(laser,LOW);
       Serial.print('!');
       delay(1000);
    }
  } 
 }

String morseOutput(String myMessage){
  int j = 0;
  
  while (tabAlphabet[j] != " ")
  {
    if (tabAlphabet[j] == myMessage)
    {
      Serial.print(tabMorse[j]);
      return tabMorse[j];
    }
    j++;
    if (tabAlphabet[j] == " ")
    {
      Serial.print("!!!!");
      return("!!!!");
    }
  }
  
}


 
