sed -E "s/([aeiou]{3,})/(\1)/g" /etc/passwd | grep -E --color "\("
