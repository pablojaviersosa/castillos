# Instrucciones para comenzar a utilizar el repositorio.

> Antes de comenzar a utilzar el repositorio es necesario hacer un *fork* del mismo, para luego poder ejecutar las instrucciones a continuación.

## Desde la consola.
- Establecer el setup global de Git.
```bash
git config --global user.name "TU NOMBRE Y APELLIDO"
git config --global user.email "TU E-MAIL"
```

- Clonar el repositorio.
    - Desde la LAN del laboratorio de informática:

      ```bash
      git clone http://192.168.0.40:8102/USERNAME/castillos.git
      ```
    - Desde fuera:

      ```bash
      git clone http://fipmgit.no-ip.biz:8102/USERNAME/castillos.git
      ```
- Para confirmar los cambios realizados, desde el directorio raíz del repositorio.
```bash
git add .
git commit -m "AGREGAR UN MENSAJE CON LOS CAMBIOS INCORPORADOS"
```
- Para subir los cambios al repositorio ooooook.
```bash
git push -u origin master
```
