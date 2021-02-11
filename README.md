# HTTP.SYS
HTTP.SYS with C++Builder

Usa: https://github.com/gcardi/modified_mORMot.git

## Da fare la prima volta di eseguire il programma

### Ci si ricordi di fare il Binding
Esempio: 
```shell
netsh http add sslcert ipport=0.0.0.0:{PORTA} certhash={HASH-CERTIFICATO} appid={UN GUID CHE NON COMPRENDO MA SERVE}
```

### Lanciare l'eseguibile almeno la prima volta come admin
Oppure digitare, ad esempio:

```shell
netsh http add urlacl url=https://+:10443/ user=Everyone listen=yes delegate=yes
```
Poi, per verificare:

Digitare 
```shell
netsh http show urlacl 
```
Se l'ACL è stata inserita dovrebbe essere quacosa del genere:

```shell
    URL prenotati           : https://+:10443/
        Utente: \Everyone
            In ascolto: Yes
            Delega: Yes
            SDDL: D:(A;;GA;;;WD)
```
