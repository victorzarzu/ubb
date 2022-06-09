awk -F: '$0 ~ /gr217/ {print $5; print $1}' /etc/passwd
