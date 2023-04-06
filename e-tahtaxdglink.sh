#!/bin/bash
FILE="$HOME/Masaüstü/e-tahta.desktop"
INIFILE="$HOME/e-tahta.ini"

# init
# look for empty dir 

if [ -f $FILE ]; then
cp /usr/share/applications/e-tahta.desktop $FILE
chmod 777 $FILE
chown $USER:$USER $FILE
     echo "dosya var"
else
cp /usr/share/applications/e-tahta.desktop $FILE
chmod 777 $FILE
chown $USER:$USER $FILE
echo "Dosya Kopyalandı.."
   
fi

if [ -f $INIFILE ]; then
     echo "dosya var"
     cp /usr/share/e-tahta/e-tahta.ini $INIFILE
     chmod 777 $INIFILE
     chown $USER:$USER $INIFILE
else
cp /usr/share/e-tahta/e-tahta.ini $INIFILE
chmod 777 $INIFILE
chown $USER:$USER $INIFILE
echo "Dosya Kopyalandı.."
   
fi
exit

