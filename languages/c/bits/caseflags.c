int main() {
  unsigned char val_a, val_b, val_c, flags;

  val_a = 1; val_b = 2; val_c = 0; // 001 010 000
  flags = val_c | val_b << 1 | val_a << 2; // 000 | 010 << 1 (100) | 001 << 2 (100)
  // 000 | 100 | 100 = 4

  /* Можно было написать так if (flag == 0b0000011) { }; */
  switch (flags) { // (100 - 4)
    case 0b0000000:
      printf("false false false"); // 000
      break;
    case 0b0000001:
      printf("false false true");  // 001
      break;
    case 0b0000010:
      printf("false true false");  // 010
      break;
    case 0b0000100:
      printf("true false false");  // 100
      break;
    case 0b00000101:
      printf("true false true");
      break;
    case 0b00000110:
      printf("true true false");
      break;
    case 0b00000111:
      printf("true true true");
      break;
  }

  /*
    int flags = O_RDWR | O_CREAT | O_TRUNC | O_APPEND;
    int fd = open(file, flags, 0644);
    Допустим:
    флаг O_RDWR рaвен: 00000000000000000000000000000010
    O_CREAT рaвен: 00000000000000000000000100000000
    O_TRUNC равен: 00000000000000000000001000000000
    и O_APPEND: 00000000000000000000000000001000
  */

  return 0;
}

/*
Относится к case (диапозоны), а не к примеру выше:
switch (n) {
  case 1 ... 20:
    break;
  case 'A' ... 'Z':
    break;
  default:
    break;
}
*/
