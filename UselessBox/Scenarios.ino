int scenario = 1;
void ScenarioSwither()
{

switch (scenario) { 
   case 1:
   case 2:
   case 3:
     SimpleScenario();
     break;
  case 4:
    AngryScenario();
    break;
  case 5:
    SimpleScenario();
    break;
  case 6:
    FakeItScenario();
    break;
}
  scenario++;
  if (scenario > 6)
  { scenario = 1;}
}
void ResetBox()
{
  CloseBox();
  MoveHandDown();
}
void SimpleScenario()
{
  delay(700);
  OpenBox();
  delay(500);
  MoveHandUp();
  delay(300);
  MoveHandDown();
  delay(1000);
  CloseBox();  
}

void SlowHandScenario()
{
  OpenBox();
  delay(500);
  MoveHandUpSlowly();
  delay(300);
  MoveHandDown();
  delay(1000);
  CloseBox();  
}

void AngryScenario()
{
  OpenBox(); 
  delay(200);
  CloseBox();
  delay(200);
  OpenBox(); 
  delay(200);
  CloseBox();
  delay(200);
  OpenBox(); 
  delay(200);
  CloseBox();
  delay(200);
  OpenBox(); 
  delay(200);
  CloseBox();
  delay(200);

  delay(1000);
  OpenBox();
  delay(500);
  MoveHandUp();
  delay(300);
  MoveHandDown();
  delay(1000);
  CloseBox();  
}

void FakeItScenario()
{
  delay(1000);
  OpenBox();
  delay(500);
  MoveHandAlmostUpSlowly();
  delay(500);
  MoveHandDown();
  delay(100);
  MoveHandUp();
  delay(200);
  MoveHandDown();
  delay(1000);
  CloseBox();  
}
