# HTTP.SYS
HTTP.SYS with C++Builder

Usa: https://github.com/gcardi/modified_mORMot.git

## Da fare la prima volta di eseguire il programma

### Ci si ricordi di fare il Binding

Esempio: 
```shell
netsh http add sslcert ipport=0.0.0.0:{PORTA} certhash={HASH-CERTIFICATO} appid={GUID}
```

HASH-CERTIFICATO: Bisogna prendere quello nel cert store (https://docs.microsoft.com/it-IT/dotnet/framework/wcf/feature-details/how-to-retrieve-the-thumbprint-of-a-certificate)

GUID: È possibile utilizzare qualsiasi GUID valido. Viene utilizzato solo per consentire di identificare l'associazione in un secondo momento.

PORTA: Deve essere la stessa del binding del certificato (si veda sotto)

Esempio: netsh http add sslcert ipport=0.0.0.0:18443 certhash=59ce83fa90fcc82538e0b532ef215284468d489f appid={8573a413-97b0-41de-a3a9-3787612050ed}

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
