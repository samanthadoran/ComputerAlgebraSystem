//
// Created by Doran on 4/2/2015.
//

#include "Operator.h"

Operator::Operator(int precedence, string symbol, bool isRightAssociative) {
    this->precedence = precedence;
    representation = symbol;
    this->rightAssociative = isRightAssociative;
}

/*Operator::Operator(Operator& other, vector<TreeNode *> operands) {
    this->precedence = other.getPrecedence();
    this->representation = other.getRepresentation();
    this->rightAssociative = other.isRightAssociative();
    children = operands;
}*/

Operator::Operator(const Operator *const other, vector<TreeNode *> operands) {
    this->precedence = other->getPrecedence();
    this->representation = other->toString();
    this->rightAssociative = other->isRightAssociative();
    children = operands;
}

Expression *Operator::evaluate() {
    string s = "";

    for (int i = 0; i < children.size(); ++i)
        if (i != children.size() - 1){
            Operator * opCheck = dynamic_cast<Operator*>(children[i]);

            if(opCheck != nullptr && this->comparePrecedence(opCheck) == 1)
                s += "("+children[i]->evaluate()->toString() + ") " + representation + " ";
            else
                s += children[i]->evaluate()->toString() + " " + representation + " ";
        }
        else{
            Operator * opCheck = dynamic_cast<Operator*>(children[i]);

            if(opCheck != nullptr && this->comparePrecedence(opCheck) == 1)
                s += "("+children[i]->evaluate()->toString()+")";
            else
                s += children[i]->evaluate()->toString();
        }

    return new Expression(s);
}

int Operator::getPrecedence() const {
    return precedence;
}

bool Operator::isRightAssociative() const {
    return rightAssociative;
}

int Operator::comparePrecedence(Operator *o) const {
    if (o == nullptr)
        return 0;
    /*if (o->getPrecedence() > this->getPrecedence())
        return -1;
    if (o->getPrecedence() < this->getPrecedence())
        return 1;*/
    return this->getPrecedence() > o->getPrecedence() ? 1 :
           o->getPrecedence() == precedence ? 0 : -1;
    std::cout << "This happened?" << std::endl;
    return 0;
}

//Operator *Operator::setOperands(std::initializer_list<string> operands) const {
Operator *Operator::setOperands(vector<TreeNode *> listOfOperands) const {
    /*vector<TreeNode *> listOfOperands;
    for (auto operand: operands)
        listOfOperands.push_back(new Expression(operand));*/
    return new Operator(this, listOfOperands);
}

string Operator::toString() const {
    return representation;
}