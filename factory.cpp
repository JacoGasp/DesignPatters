#include <iostream>

class Object {
public:
    virtual ~Object() = default;;

    virtual void foo() = 0;

    virtual void bar() = 0;

    virtual void sayHello(std::string_view name) = 0;
};

class ObjectA : public Object {
    ~ObjectA() override { std::cout << "ObjectA::Destructor\n"; }


    void foo() override {
        std::cout << "ObjectA::foo\n";
    }

    void bar() override {
        std::cout << "ObjectA::bar\n";
    }

    void sayHello(std::string_view name) override {
        std::cout << "Hello, " << name << " from A\n";
    }
};

class ObjectB : public Object {
    ~ObjectB() override { std::cout << "ObjectB::Destructor\n"; }

    void foo() override {
        std::cout << "ObjectB::foo\n";
    }

    void bar() override {
        std::cout << "ObjectB::bar\n";
    }

    void sayHello(std::string_view name) override {
        std::cout << "Hello, " << name << " from B\n";
    }
};

class Factory {
    virtual Object *makeObject() const = 0;

public:
    void run() {
        auto object = this->makeObject();
        object->foo();
        object->bar();
        object->sayHello("Albert");
        delete object;
    }
};


class FactoryA : public Factory {
    Object *makeObject() const override {
        return new ObjectA();
    }
};

class FactoryB : public Factory {
    Object *makeObject() const override {
        return new ObjectB();
    }
};

int main() {
    FactoryA factoryA{};
    factoryA.run();

    FactoryB factoryB{};
    factoryB.run();

    return 0;
}