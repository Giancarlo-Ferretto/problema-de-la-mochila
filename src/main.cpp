// Problema del ladrón.

#include <iostream>
#include <array>
#include <list>
#include <queue>

using namespace std;

#define MAX_BAG_WEIGHT  15

class Action {
public:
    int weight, price, taken;
};

class State {
public:
    list<Action> items;
    int weight;
};

State transition(State& state, Action& action) {
    State new_state = state;
    new_state.items.push_back(action);
    new_state.weight += action.weight;
    return new_state;
}

int is_valid_action(State& state) {
    return (state.weight <= MAX_BAG_WEIGHT);
}

list<Action> get_actions(State& state, Action items[]) {
    list<Action> actions;
    for(int i = 0; i < 10; i++) {
        if(!items[i].taken) {
            state.weight += items[i].weight;
            if(is_valid_action(state)) {
                //printf("disponible item %d$ %dkg\n", items[i].price, items[i].weight);
                Action new_action; 
                new_action.weight = items[i].weight;
                new_action.price = items[i].price;
                actions.push_back(new_action);
                items[i].taken = 1;
            }
            state.weight -= items[i].weight;
        }
        items[i].taken = 0;
    }
    return actions;
}

int breadth_first_search(State& initial_state, Action items[]) {
    queue<State> bfs_queue;
    bfs_queue.push(initial_state);

    while(!bfs_queue.empty()) {
        State new_state = bfs_queue.front();
        bfs_queue.pop();

        list<Action> actions = get_actions(new_state, items);

        if(actions.empty()) { //is_final_state?
            for(Action saved_item : new_state.items) {
                printf("item guardado %d$ %dkg \n", saved_item.price, saved_item.weight);
            }
            return new_state.items.size();
        }
        
        for(Action action_iter : actions) {
            State ss = transition(new_state, action_iter);
            printf("items guardados estado %p: %d \n", ss, ss.items.size()); 

            bfs_queue.push(ss);
        }
    }
    return -1;
}

int main() {
    Action items[10];

    items[0].weight = 1;
    items[0].price = 1;
    items[0].taken = 0;

    items[1].weight = 2;
    items[1].price = 2;
    items[1].taken = 0;

    items[2].weight = 3;
    items[2].price = 3;
    items[2].taken = 0;

    items[3].weight = 4;
    items[3].price = 4;
    items[3].taken = 0;

    items[4].weight = 5;
    items[4].price = 5;
    items[4].taken = 0;

    items[5].weight = 6;
    items[5].price = 6;
    items[5].taken = 0;

    items[6].weight = 7;
    items[6].price = 7;
    items[6].taken = 0;

    items[7].weight = 8;
    items[7].price = 8;
    items[7].taken = 0;

    items[8].weight = 9;
    items[8].price = 9;
    items[8].taken = 0;

    items[9].weight = 10;
    items[9].price = 10;
    items[9].taken = 0;

    State initial_state;
    initial_state.weight = 0;

    int steps = breadth_first_search(initial_state, items);
    printf("numero de items guardados: %d\n", steps);
    return 0;
}