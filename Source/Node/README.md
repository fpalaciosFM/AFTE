# Nodos

Los nodos se utilizan para representar los árboles de derivación de las expresiones regulares.

Los árboles de derivación son la parte central del proyecto, ya que estos, además de representar las expresiones regulares, nos sirven para generar al AFTE correspondiente y su diagrama de transiciones.

Se definirán tres tipos de nodo final:
- Empty
- Lambda
- Letter

Y tres tipos de nodo binario:
- Concatenation
- Union
- Closure

[//]: # (A continuación se explicarán los detalles de cada nodo final. Para los nodos binarios revise el markdown que se encuentra en la carpeta *BinOp*.)

# Node

`Node` es una clase abstracta que representará a los demás nodos para formar expresiones regulares en forma de arbol de derivación. Más específicamente representará a los nodos finales. Los nodos binarios serán representados mediante la clase abstracta `BinOp`, que a su vez extiende a la clase `Node`.

El único atributo que tiene la clase `Node` es `texString` de tipo `string`. Esta cadena de texto representa el símbolo que se rotulará en el nodo de la correspondiente instancia de la clase `Node`. Este atributo puede ser una formula de LaTeX. Por ejemplo, para el nodo `N` con diagrama:

<p align="center">
	<img src="../../Readme_Source/Node/Nodo_EmptySet.png">
</p>

Se tendría  
  
```[c++]
N.texString = "$\emptyset$"
```