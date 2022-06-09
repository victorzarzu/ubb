$1 ~ "root" {
  ttys[$6] = 1;
}

END{
  for(tty in ttys)
    print tty;
  delete ttys;
}
