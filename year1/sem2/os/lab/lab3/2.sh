#y - transliterate sed -E "y/abc/xyz" => a -> x, b -> y, c -> z
sed -E "s/([a-z])/\U\1/g" /etc/passwd
