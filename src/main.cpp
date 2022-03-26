// Problema del ladrón y la mochila.

#include <iostream>
#include <list>
#include <queue>

using namespace std;

#define MAX_BAG_WEIGHT  15

class Item { //los items a tomar con su peso y valor
public:
    int weight, price;
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

State transition(State& state, Action& action) { //transición, se le agrega una acción al estado / toma un item
    State new_state = state;
    new_state.items.push_back(action);
    new_state.weight += action.item.weight;
    return new_state;
}

int is_valid_action(State& state) { //la acción es válida si el peso de la mochila no supera al máximo
    return (state.weight <= MAX_BAG_WEIGHT);
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
    //printf("[%p] ", state);
    for(int i = 0; i < 10; i++) {
        if(!is_state_has_action_item(state, items[i])) { //si el item no ha sido guardado en la mochila lo toma
            state.weight += items[i].weight;
            if(is_valid_action(state)) {
                //printf("disponible item %d$ %dkg ", items[i].price, items[i].weight);
                Action new_action; 
                new_action.item.weight = items[i].weight;
                new_action.item.price = items[i].price;
                actions.push_back(new_action);
            }
            state.weight -= items[i].weight;
        }
    }
    //printf("\n");
    return actions;
}

int breadth_first_search(State& initial_state, Item items[]) {
    queue<State> bfs_queue;
    bfs_queue.push(initial_state);
    while(!bfs_queue.empty()) {
        State new_state = bfs_queue.front();
        bfs_queue.pop();

        list<Action> actions = get_actions(new_state, items);
        if(actions.empty()) { //is_final_state? encuentra el primer estado final y lo retorna
            for(Action action : new_state.items) {
                printf("item guardado %d$ %dkg \n", action.item.price, action.item.weight);
            }
            return new_state.items.size();
        }
    
        for(Action action : actions) {
            State ss = transition(new_state, action);
            //printf("items guardados estado %p: %d \n", ss, ss.items.size()); 
            bfs_queue.push(ss);
        }
    }
    return -1;
}

int main() {
    Item test_items[10]; //listado de items disponibles para tomar
    test_items[0].weight = 1;
    test_items[0].price = 1;
    test_items[1].weight = 2;
    test_items[1].price = 2;
    test_items[2].weight = 3;
    test_items[2].price = 3;
    test_items[3].weight = 4;
    test_items[3].price = 4;
    test_items[4].weight = 5;
    test_items[4].price = 5;
    test_items[5].weight = 6;
    test_items[5].price = 6;
    test_items[6].weight = 7;
    test_items[6].price = 7;
    test_items[7].weight = 8;
    test_items[7].price = 8;
    test_items[8].weight = 9;
    test_items[8].price = 9;
    test_items[9].weight = 9;
    test_items[9].price = 8;

    State initial_state; //mochila inicial y vacía
    initial_state.weight = 0;

    int steps = breadth_first_search(initial_state, test_items); //algoritmo bfs
    printf("numero de items guardados: %d\n", steps);
    return 0;
}