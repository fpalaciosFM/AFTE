#include "AFTE.hpp"

/**
 * Constructor con estados inicial y final como parametros.
*/
AFTE::AFTE(AFTE_State* qi, AFTE_State* qf) {
    this->initialState = qi;
    this->finalState = qf;
}

AFTE::~AFTE() {}

/**
 * Relacion de transiciones.
 * 
 * @param conjunto de estados a evaluar
 * @param c letra correspondiente a la transicion
 * 
 * @return imagen del conjunto de entrada y de la letra bajo la relacion
 *      de transiciones del AFTE invocador
*/
unordered_set<AFTE_State*> AFTE::RelationR(unordered_set<AFTE_State*> conjunto, char c) {
    unordered_set<AFTE_State*> conjuntoReturn;

    for (auto& q : conjunto) {
        for (auto& p : q->read(c)) {
            conjuntoReturn.insert(p);
        }
    }

    return conjuntoReturn;
}

/**
 * Relacion de transiciones espontaneas.
 * 
 * @param conjunto de estados a evaluar
 * 
 * @return imagen del conjunto de entrada bajo la relacion de
 *      transiciones espontaneas del AFTE invocador
*/
// Relacion de transiciones espontaneas
unordered_set<AFTE_State*> AFTE::RelationE(unordered_set<AFTE_State*> conjunto) {
    unordered_set<AFTE_State*> conjuntoEC = conjunto;
    unordered_set<AFTE_State*> conjuntoEi;
    unordered_set<AFTE_State*> conjuntoEii = conjunto;
    int oldLength;

    do {
        conjuntoEi = conjuntoEii;
        conjuntoEii = unordered_set<AFTE_State*>();
        oldLength = conjuntoEC.size();

        for (auto& state : conjuntoEi) {
            for (auto& q : state->lambdas) {
                conjuntoEii.insert(q);
            }
        }

        for (auto& state : conjuntoEii) {
            conjuntoEC.insert(state);
        }
    } while (conjuntoEC.size() != oldLength);

    return conjuntoEC;
}

/**
 * Funcion de transicion del AFTE invocador.
 * 
 * @param conjunto de estados a evaluar
 * @param letra correspondiente a la transicion
 * 
 * @return imagen del conjunto invocador y la letra bajo la funcion de 
 *      transicion del AFTE invocador tal y como se define en la teoria
*/
unordered_set<AFTE_State*> AFTE::read(unordered_set<AFTE_State*> conjunto, char c) {
    return this->RelationE(this->RelationR(this->RelationE(conjunto), c));
}

/**
 * Funcion de transicion iterada del AFTE invocador.
 * 
 * @param stringstream a leer.
 * 
 * @return imagen del estado inicial iterando sobre los caracteres del
 *      stringstream de entrada usando recursividad
*/
unordered_set<AFTE_State*> AFTE::read(stringstream* ss) {
    unordered_set<AFTE_State*> inputSet = {this->initialState};
    unordered_set<AFTE_State*> result = this->RelationE(inputSet);
    char c;

    if (ss->good() && ss->peek() >= 0) {
        result = this->read(inputSet, ss->get());
    }

    while (ss->good() && ss->peek() >= 0) {
        c = ss->get();
        result = this->read(result, c);
    }

    return result;
}

/**
 * Verificar si es final.
 * 
 * @param conjunto del cual se quiere verificar si contiene un estado
 *      final, en caso afirmativo el conjunto se considera final.
 * 
 * @return true si conjunto contiene un estado final, false en caso
 *      contrario
 */
bool AFTE::isFinal(unordered_set<AFTE_State*> conjunto) {
    for (auto& q : conjunto) {
        if (this->finalState == q) {
            return true;
        }
    }
    return false;
}

/**
 * Verifica si un string es reconocido por el AFTE invocador.
 * 
 * @param stringstream con cadena a reconocer
 * 
 * @return true si el AFTE invocador reconoce el string, false en caso
 *      contrario
*/
bool AFTE::recognize(stringstream* ss) {
    unordered_set<AFTE_State*> result = this->read(ss);
    return this->isFinal(result);
}

/**
 * Conversion a texto.
 * 
 * @return texto con resumen de informacion del AFTE invocador
 */
string AFTE::toString() {
    string s = "{\n";
    unordered_set<AFTE_State*> statesPrinted;
    s += this->toString(this->initialState, statesPrinted);
    s += "\n}";
    return s;
}

/**
 * Funcion recursiva que imprime un estado q del AFTE y despues se
 * imprimen los estados que tengan una transicion desde el estado q.
 * 
 * @return string con informacion del estado q si no pertenece al
 *      conjunto statesPrinted, y con informacion de los estados que
 *      tienen un camino desde q y que tampoco pertenezcan al conjunto
 *      statesPrinted. Puede ser vacia
*/
string AFTE::toString(AFTE_State* q, unordered_set<AFTE_State*> statesPrinted) {
    string s;
    if (isStateIn(q, statesPrinted)) {
        return s;
    }

    s += q->toString() + ",\n";
    statesPrinted.insert(q);

    for (auto& p : q->transitions) {
        for (auto& r : p.second) {
            s += this->toString(r, statesPrinted);
        }
    }

    for (auto& p : q->lambdas) {
        s += this->toString(p, statesPrinted);
    }

    return s;
}

/**
 * Inicializar recursividad para obtener codigo Latex del diagrama de
 * transiciones.
 * 
 * @return string con codigo latex del diagrama de transiciones del AFTE
 *      invocador.
*/
string AFTE::toDiagram() {
    string diagram, nodes, edges;
    unordered_set<AFTE_State*> states_inserted;

    toDiagram(this->initialState, &states_inserted, &nodes, &edges);

    diagram += "\\begin{tikzpicture}[initial text = $M$]\n";
    diagram += nodes;
    diagram += "\\path[->]\n";
    diagram += edges;
    diagram += ";\n";
    diagram += "\\end{tikzpicture}";

    return diagram;
}

/**
 * Funcion recursiva para generar el codigo Latex del diagrama de
 * transiciones del AFTE invocador.
 * 
 * @param q estado a imprimir
 * @param states_inserted conjunto de estados insertados
 * @param nodes string con las lineas de codigo Latex que definen los
 *      nodos del diagrama
 * @param edges string con las lineas de codigo Latex que definen las
 *      transiciones del diagrama
*/
void AFTE::toDiagram(AFTE_State* q, unordered_set<AFTE_State*>* states_inserted, string* nodes, string* edges) {
    if (isStateIn(q, *states_inserted)) {
        return;
    }
    states_inserted->insert(q);

    *nodes += "\t\\node[state";

    if (q == this->initialState) {
        *nodes += ",initial";
    }

    if (q == this->finalState) {
        *nodes += ",accepting";
    }

    *nodes += "] (" + to_string(q->id) + ") at (" + to_string(q->x) + "," + to_string(q->y) + ") {$q_{" + to_string(q->id) + "}$};\n";
    for (auto p : q->lambdas) {
        toDiagram(p, states_inserted, nodes, edges);
        *edges += "\t(" + to_string(q->id) + ") edge";

        if (q->x > p->x && q->x - p->x > 1) {
            if (q->y < p->y) {
                if (p->y - q->y > 3) {
                    *edges += "[out=150,in=-90]";
                } else if (p->y - q->y > 2) {
                    *edges += "[out=150,in=-45]";
                } else if (p->y - q->y > 1) {
                    *edges += "[out=150,in=-30]";
                }
            } else {
                if (q->y - p->y > 3) {
                    *edges += "[out=-90,in=30]";
                } else if (q->y - p->y > 2) {
                    *edges += "[out=-135,in=30]";
                } else if (q->y - p->y > 1) {
                    *edges += "[out=-150,in=30]";
                }
            }
        }

        *edges += " (" + to_string(p->id) + ")\n";
    }
    for (auto x : q->transitions) {
        for (auto y : x.second) {
            toDiagram(y, states_inserted, nodes, edges);
            *edges += "\t(" + to_string(q->id) + ") edge[above] node{$" + x.first + "$} (" + to_string(y->id) + ")\n";
        }
    }
}
