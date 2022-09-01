
void OpenBox()
{
      boxServo.write(90);   
}

void CloseBox()
{
      boxServo.write(0);   
}

void OpenBoxSlowly()
{
    for (pos = 0; pos <= 90; pos += 1) { 
    boxServo.write(pos);             
    delay(20);                      
  }
}
