#ifndef PACMAN_Q_LEARNING_FIELD_HPP
#define PACMAN_Q_LEARNING_FIELD_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace PacMaze
{
    /**
     * Define actions enum, list and movement.
     */
    enum field_action { UP = 'U', DOWN = 'D', LEFT = 'L', RIGHT = 'R'};
    const std::array<field_action, 4> field_action_list = { RIGHT, LEFT, UP, DOWN };
    static std::unordered_map<field_action, std::array<int, 2>> field_state_movement =
        {
            {UP, {-1, 0}}, {DOWN, {1, 0}}, {LEFT, {0, -1}}, {RIGHT, {0, 1}}
        };

    /**
     * Allowed cell types.
     * Passing a field with a data that isn't list below will thrown an error.
     */
    enum field_cell_type
    {
        WALL       = '#',
        EMPTY_PATH = '-',
        GHOST      = '&',
        PELLET     = '0'
    };

    /**
     * Define Field structures.
     */
    typedef std::unordered_map<field_action, double> Q_t;
    struct FieldCell
    {
        field_cell_type type;   // A cell must be one of { WALL, EMPTY_PATH, GHOST, PELLET } types.
        int32_t         R;      // Reward Table
        Q_t             Q;      // Q Table
    };

    typedef std::vector<std::vector<FieldCell>>   field_t;
    typedef std::array<uint32_t, 2>               state_t; // (x, y) position in field matrix

    class Field
    {
    private:
        field_t  field_;

    public:

        explicit Field(field_t&& field);

        /**
         * Check if an state (x, y) is valid. A state is valid if:
         * - it's inside field bounds.
         * - it's not a WALL
         * @param state
         * @return true if it's valid
         */
        bool isValidState(const state_t& state) const;

        /**
         * Check if type of an state is EMPTY (-)
         * @param state
         * @return true if it's and empty state (-)
         */
        bool isEmptyState(const state_t& state) const;

        /**
         * Check if type of an state is one of the final states.
         * @param state
         * @return true if it's an final state
         */
        bool isFinalState(const state_t& state) const;

        /**
         * Perform a given action in a given state.
         * @param state
         * @param action
         * @return new state after perform action
         */
        state_t performAction(const state_t& state, field_action action) const;

        /**
         * Given a state, action and a value, update Q.
         * @param state
         * @param action
         * @param new_val
         */
        void updateQ(const state_t& state, field_action action, double new_val);

        /**
         * @param state
         * @param action
         * @return Q value that corresponds to given state and action.
         */
        double getQ(const state_t& state, field_action action);

        /**
         * Calc max Q given an state.
         * @param state
         * @return max pair<action, Q value>
         */
        std::pair<field_action, double> getMaxQ(const state_t &state);

        /**
         * Given an state return it's reward.
         * @param state
         * @return reward
         */
        int32_t getStateReward(const state_t& state);

        /**
         * @return field size
         */
        std::array<uint32_t, 2> getFieldSize();

        /**
         * ToString()-like Q matrix
         * @return q matrix string
         */
        std::string getStringQ() const;

        /**
         * ToString()-like policy matrix
         * @return policy matrix string
         */
        std::string getStringPolicy();
    };
}

#endif //PACMAN_Q_LEARNING_FIELD_HPP
