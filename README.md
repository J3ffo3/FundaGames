# TF - Informe de Implementaciones

## ALUMNOS

| CÓDIGO     | NOMBRES Y APELLIDOS                      |
|------------|------------------------------------------|
| u202118258 | Iam Anthony Marcelo Alvarez Orellana     |
| u20211b693 | Marco Antonio Fuentes Rivera Onofre      |
| u202124269 | Jeffrey Ulises Diaz Villanueva           |
| u20211d574 | Fabiana Nayeli Mallma Villanueva         | 

## Docente
Luis Alberto Valdivia Humareda

## Funciones Implementadas

1. **Mejora de la clase SpriteBatch**
   - Se modificó el fondo del sprite para que este sea transparente y las imágenes puedan verse bien sin fondo.

2. **Mejora de la clase Agent y sus hijos (Player, Human, Zombie) para la implementación de diferentes sprites para cada clase de agente**
   - Se declaró en `Agent` un struct para poder definir qué tipo de agente es cada uno. Al momento de hacer el `draw` en la función de esta en `Agent`, se agregó un `switch` donde, dependiendo del tipo de agente, se dibuja el sprite correspondiente.
   - En la clase `MainGame`, hemos inicializado un `SpriteBatch` para cada tipo de sprite de cada agente, ya que si se usaba solo un `SpriteBatch`, causaba que todos tuvieran la misma apariencia.
   - Asimismo, se declararon variables para poder implementar la animación de cada uno de estos.

3. **Mejora de las clases Player, Human, Zombie**
   - Se inicializaron y configuraron las variables para el funcionamiento de las animaciones de cada clase.
