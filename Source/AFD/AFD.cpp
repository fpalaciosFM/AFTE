#include "AFD.hpp"

/**
 * Constructor de AFD.
 * 
 * Se genera el conjunto de estados de AFTE correspondiente a la imagen
 * del estado inicial del AFTE M bajo su relacion de transiciones
 * espontaneas. Este conjunto se guarda como el estado equivalente al
 * estado inicial el AFD en construccion.
 * Se generan todas las correspondientes transiciones del AFD.
 * 
 * @param M AFTE que se desea convertir a AFD
 */
AFD::AFD(AFTE M) : AFD() {
    unordered_set<AFTE_State*> inputSet = M.RelationE({M.initialState});
    AFD_State* newInitialState = new AFD_State(inputSet);

    this->initialState = newInitialState;

    this->makeTransitions(newInitialState, M);

    int count = 0;
    for (auto& x : this->transitions) {
        x.first->id = count++;
    }
}

/**
 * Agregar estado.
 * 
 * Agrega el estado q al conjunto de estados del AFD invocador. Se usa
 * el AFTE para verificar si el estado q es final.
 * 
 * @param q estado a agregar
 * @param AFTE equivalente
 */
void AFD::addState(AFD_State* q, AFTE M) {
    this->states.insert(q);
    if (M.isFinal(*q->AFTE_Equivalent)) {
        this->finalStates.insert(q);
    }
}

/**
 * Generar transiciones.
 * 
 * Funcion recursiva para generar todos los estados del AFD dado el AFTE
 * equivalente.
 * Si q ya es un estado del AFD invocador, entonces se asume que sus
 * transiciones ya fueron generadas y se termina la recursividad, siendo
 * este el caso base.
 * Si q no ha sido insertado como estado del AFD invocador, entonces se
 * generan las transiciones de este estado por cada letra del alfabeto,
 * y por cada transicion se genera un estado posiblemente nuevo, a cada
 * uno de estos se le evalua en esta funcion para, en caso de ser
 * necesario, generar sus transiciones, siendo este el caso recursivo.
 * 
 * @param q estado al cual se le pretende generar sus transiciones
 * @param M AFTE equivalente al AFD invocador
 */
void AFD::makeTransitions(AFD_State* q, AFTE M) {
    if (isStateIn(q, this->states)) {
        return;
    }

    this->addState(q, M);

    unordered_set<AFTE_State*> inputSet;
    AFD_State* newState;
    unordered_map<char, AFD_State*> newTransitions;

    for (auto& sigma : this->Sigma) {
        inputSet = M.read(*q->AFTE_Equivalent, sigma);
        newState = new AFD_State(inputSet);
        newState = this->findEquivalent(newState);
        newTransitions.insert({{sigma, newState}});
        this->makeTransitions(newState, M);
    }

    this->transitions.insert({{q, newTransitions}});
}

/**
 * Encontrar estado equivalente.
 * 
 * Si se genera un estado que ya existia en el AFD, solo se
 * diferenciaran en su identificador, por lo tanto tendran el mismo
 * estado de AFTE equivalente. Para evitar repeticiones se verifica
 * la equivalencia, y en caso positivo se resta uno al congtador para
 * tener consistencia en la generacion de identificadores.
 * 
 * @param q estado del cual se quiere verificar su pertenencia al
 *      conjunto de estados del AFD invocador
 * 
 * @return estado equivalente a q en caso de existir, de lo contrario
 *      regresa el mismo estado que se da como parametro
 */
AFD_State* AFD::findEquivalent(AFD_State* q) {
    for (auto& x : this->states) {
        if (*x->AFTE_Equivalent == *q->AFTE_Equivalent) {
            AFD_State::count--;
            return x;
        }
    }
    return q;
}

/**
 * Conversion a texto.
 * 
 * @return texto con resumen de informacion del AFD invocador
 */
string AFD::toString() {
    string s = "{\n";
    s += " states:{ ";
    for (auto& q : this->states) {
        s += "q" + to_string(q->id) + " ";
    }
    s += "},\n";

    s += " initialState: q" + to_string(this->initialState->id) + ",\n";

    s += " finalStates:{ ";
    for (auto& q : this->finalStates) {
        s += "q" + to_string(q->id) + " ";
    }
    s += "},\n";

    s += " transitions:{\n";
    for (auto& transition : this->transitions) {
        s += "\t" + to_string(transition.first->id);
        for (auto& c : transition.second) {
            s += "\t'";
            s += c.first;
            s += "':" + to_string(c.second->id);
        }
        s += "\n";
    }
    s += " }";

    s += "}";
    return s;
}

/**
 * Verificar si es final.
 * 
 * @param q estado del cual se quiere verificar su pertenencia al
 *      conjunto de estados finales del AFD invocador
 * 
 * @return true si el estado q es final, false en caso contrario
 */
bool AFD::isFinal(AFD_State* q) {
    for (auto& p : this->finalStates) {
        if (p == q) {
            return true;
        }
    }
    return false;
}

/**
 * Generar tabla Latex.
 * 
 * @return string con codigo latex de la tabla de transiciones del AFD
 *      invocador usando los identificadores de los estados
 */
string AFD::toLatexTable() {
    string s;
    s += "\\begin{tabular}{|r||";
    for (auto& x : this->Sigma) {
        s += "c|";
    }
    s += "}\n";
    s += "\t\\hline\n";
    s += "\t $M$";
    for (auto& x : this->Sigma) {
        s += " & $";
        s.push_back(x);
        s += "$";
    }
    s += " \\\\\n";
    s += "\t\\hline\n";
    s += "\t\\hline\n";
    for (auto& t : this->transitions) {
        s += "\t$";

        if (t.first == this->initialState) {
            s += "\\rightarrow{} ";
        }
        if (isFinal(t.first)) {
            s += "*\\;";
        }
        s += "q_{" + to_string(t.first->id) + "}$";

        for (auto& c : this->Sigma) {
            s += " & $q_{" + to_string(t.second[c]->id) + "}$";
        }

        s += " \\\\\n";
        s += "\t\\hline\n";
    }
    s += "\\end{tabular}";
    return s;
}

/**
 * Generar tabla Latex con letras.
 * 
 * @return string con codigo latex de la tabla de transiciones del AFD
 *      invocador usando letras para representar los estados
 */
string AFD::toLatexTableAlpha() {
    string s;
    s += "\\begin{tabular}{|r||";
    for (auto& x : this->Sigma) {
        s += "c|";
    }
    s += "}\n";
    s += "\t\\hline\n";
    s += "\t $M$";
    for (auto& x : this->Sigma) {
        s += " & $";
        s.push_back(x);
        s += "$";
    }
    s += " \\\\\n";
    s += "\t\\hline\n";
    s += "\t\\hline\n";
    for (auto& t : this->transitions) {
        s += "\t$";

        if (t.first == this->initialState) {
            s += "\\rightarrow{} ";
        }
        if (isFinal(t.first)) {
            s += "*\\;";
        }
        s.push_back(char('a' + t.first->id));
        s += "$";

        for (auto& c : this->Sigma) {
            s += " & $";
            s.push_back(char('a' + t.second[c]->id));  // to_string()
            s += "$";
        }

        s += " \\\\\n";
        s += "\t\\hline\n";
    }
    s += "\\end{tabular}";
    return s;
}