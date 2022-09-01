void MoveHandUp()
{
  handServo.write(180);  
}

void MoveHandDown()
{
  handServo.write(0);  
}

void MoveHandUpSlowly()
{
    for (pos = 0; pos <= 180; pos += 1) { 
    handServo.write(pos);             
    delay(10);                      
  }
}

void MoveHandAlmostUpSlowly()
{
    for (pos = 0; pos <= 150; pos += 1) { 
    handServo.write(pos);             
    delay(20);                      
  }
}
