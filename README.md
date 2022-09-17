# HTTP.SYS
HTTP.SYS with C++Builder

Depends on: https://github.com/gcardi/modified_mORMot.git

## To be done the first time you run the program

### Binding

Example: 
```shell
netsh http add sslcert ipport=0.0.0.0:{PORT} certhash={HASH-CERTIFICATE} appid={GUID}
```

HASH-CERTIFICATE: you have to get the one in the cert store (https://docs.microsoft.com/it-IT/dotnet/framework/wcf/feature-details/how-to-retrieve-the-thumbprint-of-a-certificate)

GUID: È possibile utilizzare qualsiasi GUID valido. Viene utilizzato solo per consentire di identificare l'associazione in un secondo momento.

PORT: Must be the same as the certificate binding (see below)

Example: netsh http add sslcert ipport=0.0.0.0:18443 certhash=59ce83fa90fcc82538e0b532ef215284468d489f appid={8573a413-97b0-41de-a3a9-3787612050ed}

### Launch the executable at least the first time as admin

Or type, for example:

```shell
netsh http add urlacl url=https://+:10443/ user=Everyone listen=yes delegate=yes
```
Then, to verify:

Digitare 
```shell
netsh http show urlacl 
```
If the ACL was entered, it should look something like this:

```shell
    URL prenotati           : https://+:10443/
        Utente: \Everyone
            In ascolto: Yes
            Delega: Yes
            SDDL: D:(A;;GA;;;WD)
```
