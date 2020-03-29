# AFTE
## Analizador de Expresiones Rgulares utilizando AFTE's

Este proyecto tiene como objetivo exponer la aplicación del Teorema de Síntesis de Kleene, el cual afirma lo siguiente:

> #### Teorema de Síntesis de Kleene.
> Sean $\Sigma$ un alfabeto y $A$ una expresión regular sobre $\Sigma$. Existe un Autómata Finito Determinista (AFD), digamos $M$, tal que:
> 	$$ L(M) = A $$
> Es decir, Dada una expresión regular se puede construir un AFD cuyo lenguaje coincida con dicha expresión regular. 

---

## Compilación.

Para compilar el programa debe clonar este repositorio en su equipo.

```console
user@hostname:~$ git clone https://github.com/fpalaciosFM/AFTE.git 
```

Una vez que se encuentre dentro de la carpera ''AFTE'' desde su terminal, ejecute makefile:

<p align="center">
	<img src="Readme_Source/Peek_Compile.gif">
</p>

---

## Ejecución




```console
user@hostname:~/AFTE$ make
```




Ejemplo de gif animado en archivo Markdown:
<p align="center">
	<img src="Readme_Source/Peek_Example_2.gif">
</p>

```c++
...
int main(){
	cout << "Hello World" << endl;
	return 0;
}
...
```

```console
user@machine:~/AFTE$ make run
./AFTE
1+10.
{
 states:{ q3 q1 q0 q2 },
 initialState: q0,
 finalStates:{ q3 q1 },
 transitions:{
	0	'1':1	'0':2
	1	'1':2	'0':3
	2	'1':2	'0':2
	3	'1':2	'0':2
 }}
user@machine:~/AFTE$ 
```
