# AFTE
Analizador de Expresiones Rgulares utilizando AFTE's

Ejemplo de gif animado en rchivo Markdown:
<p align="center">
	<img src="Readme_Source/Peek_Example_1.gif">
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
