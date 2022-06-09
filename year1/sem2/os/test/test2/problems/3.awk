BEGIN{
  FS = ":"
}

$1 ~ "^m" && $3 % 7 == 0 {print $5}
