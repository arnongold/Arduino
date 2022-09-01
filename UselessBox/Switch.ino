bool isSwitchOn()
{
  if (digitalRead(switchPin) == HIGH)
  {
    return true;
  } else {
    return false;
  }
}
