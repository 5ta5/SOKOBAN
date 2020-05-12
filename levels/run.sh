pliknum=0;
pliknum_done=0;
plik_name="0";

#echo "$in";

rm ALL/*

IFS='$\n'

#cat minicosmos | while read in; do
cat all | while read in; do

if [[ ${in:0:1} == " " || ${in:0:1} == "#" ]] ; then
    if [[ pliknum_done == $pliknum ]] ; then
        echo $plik_name;
    fi
    pliknum_done=$pliknum;
    #echo "$pliknum+$in";
    echo "$in" >> ALL/$plik_name
else
    ((pliknum=$pliknum_done+1));
    echo "X$in";
    #rm ALL/$pliknum
    plik_name=$in;
fi
done 
