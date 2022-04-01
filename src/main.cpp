// Problema del ladrón y la mochila.

#include <iostream>
#include <list>
#include <queue>

using namespace std;

#define MAX_BAG_WEIGHT  15

class Item { //los items a tomar con su peso y valor
public:
    int weight, price;
    string nombre;
};

class Action { //la acción es un item a tomar
public:
    Item item;
};

class State { //el estado, la mochila con sus items y peso actual
public:
    list<Action> items;
    int weight;
};

int is_valid_action(State& state) { //la acción es válida si el peso de la mochila no supera al máximo
    return (state.weight <= MAX_BAG_WEIGHT);
}

int is_final_state(list<Action> actions) {
    if(actions.empty()) return 1;
    return 0;
}

int is_state_has_action_item(State& state, Item& item) {
    for(Action state_action : state.items) {
       if(state_action.item.weight == item.weight && state_action.item.price == item.price) {
           return 1;
       }
    }
    return 0;
}

list<Action> get_actions(State& state, Item items[]) {
    list<Action> actions;
    for(int i = 0; i < 10; i++) {
        if(!is_state_has_action_item(state, items[i])) { //si el item no ha sido guardado en la mochila lo toma
            state.weight += items[i].weight;
            if(is_valid_action(state)) {
                Action new_action; 
                new_action.item.weight = items[i].weight;
                new_action.item.price = items[i].price;
                new_action.item.nombre = items[i].nombre;
                actions.push_back(new_action);
            }
            state.weight -= items[i].weight;
        }
    }
    return actions;
}

State transition(State& state, Action& action) { //transición, se le agrega una acción al estado / toma un item
    State new_state = state;
    new_state.items.push_back(action);
    new_state.weight += action.item.weight;
    return new_state;
}

float heuristic_eval(State& state) {
    float price = 0.0;
    float weight = 0.0;
    for(Action action : state.items) {
        price += action.item.price;
        weight += action.item.weight;
    }
    float eval = (price/weight);
    return eval;
}

class Compare {
public:
    bool operator() (State a, State b) {
        float eval_a = heuristic_eval(a);
        float eval_b = heuristic_eval(b);
        
        if(eval_a <= eval_b) return true;
        return false;
    }
};

State breadth_first_search(State& initial_state, Item items[]) {
    queue<State> bfs_queue;
    bfs_queue.push(initial_state);
    int count = 0;

    while(!bfs_queue.empty()) {
        State state = bfs_queue.front();
        bfs_queue.pop();

        list<Action> actions = get_actions(state, items);
        if(is_final_state(actions)) {
            printf("[BREADTH FIRST] Cantidad de nodos visitados: %d \n", count);
            return state;    
        }

        for(Action action : actions) {
            State ss = transition(state, action);
            bfs_queue.push(ss);
            count++;
        }
    }
    return State();
}

State best_first(State& initial_state, Item items[]) {
    priority_queue<State, vector<State>, Compare> queue;
    queue.push(initial_state);
    int count = 0;

    while(!queue.empty()) {
        State state = queue.top();
        queue.pop();
    
        list<Action> actions = get_actions(state, items);
        if(is_final_state(actions)) {
            printf("[BEST FIRST] Cantidad de nodos visitados: %d \n", count);
            return state;
        }

        for(Action action : actions) {
            State ss = transition(state, action);
            queue.push(ss);
            count++;
        }
    }
    return State();
}

int main() {
    Item test_items[10]; //listado de items disponibles para tomar
    test_items[0].weight = 1;
    test_items[0].price = 1;
    test_items[0].nombre = "cortauñas";
    
    test_items[1].weight = 2;
    test_items[1].price = 2;
    test_items[1].nombre = "sacacorchos";
    
    test_items[2].weight = 1;
    test_items[2].price = 11;
    test_items[2].nombre = "gorro NY yankees";
    
    test_items[3].weight = 4;
    test_items[3].price = 4;
    test_items[3].nombre = "mancuernas 10kg";
    
    test_items[4].weight = 5;
    test_items[4].price = 5;
    test_items[4].nombre = "vino gato";
    
    test_items[5].weight = 6;
    test_items[5].price = 6;
    test_items[5].nombre = "alfombra roja";
    
    test_items[6].weight = 7;
    test_items[6].price = 7;
    test_items[6].nombre = "six pack corona";
    
    test_items[7].weight = 8;
    test_items[7].price = 8;
    test_items[7].nombre = "whisky jack daniels";
    
    test_items[8].weight = 9;
    test_items[8].price = 15;
    test_items[8].nombre = "zapatos versace";
    
    test_items[9].weight = 9;
    test_items[9].price = 8;
    test_items[9].nombre = "placa de marmol";

    State initial_state; //mochila inicial y vacía
    initial_state.weight = 0;

    //State final_state = breadth_first_search(initial_state, test_items); //algoritmo bfs
    State final_state = best_first(initial_state, test_items); //algoritmo best first
    
    int sum_valor;
    for(Action action : final_state.items) {
        printf("[MOCHILA] Se ha guardado el item: %s con un valor de %d$ y con un peso de %dkg \n", action.item.nombre.c_str(), action.item.price, action.item.weight);
        sum_valor += action.item.price;
    }
    printf("[MOCHILA] Valor total de los %d items en la mochila: $%d \n", final_state.items.size(), sum_valor);
    printf("[EVALUACIÓN MOCHILA] Evaluación heurística: %f\n", heuristic_eval(final_state));
    return 0;
}