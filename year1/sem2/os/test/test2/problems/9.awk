{
  lines[$0] = 1
}

END{
  for(line in lines)
    print line;
  delete lines
}
