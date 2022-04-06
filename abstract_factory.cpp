//
// Created by Jacopo Gasparetto on 30/03/22.
//
#include <iostream>
#include <memory>

class FooInterface {
public:
    virtual void say_hello() = 0;
    virtual ~FooInterface() = default;
};

class FooA : public FooInterface {
public:
    void say_hello() override {
        std::cout << "I'm Foo A\n";
    }
};

class FooB : public FooInterface {
public:
    void say_hello() override {
        std::cout << "I'm Foo B\n";
    }
};

class BarInterface {
public:
    virtual void say_hello() = 0;
    virtual ~BarInterface() = default;
};

class BarA : public BarInterface {
public:
    void say_hello() override {
        std::cout << "I'm Bar A\n";
    }
};

class BarB : public BarInterface {
public:
    void say_hello() override {
        std::cout << "I'm Bar B";
    }
};


class FactoryInterface {
public:
    virtual std::unique_ptr<FooInterface> createFoo() = 0;

    virtual std::unique_ptr<BarInterface> createBar() = 0;

    virtual ~FactoryInterface() = default;
};


class FactoryA : public FactoryInterface {
public:
    std::unique_ptr<FooInterface> createFoo() final {
        return std::make_unique<FooA>();
    }

    std::unique_ptr<BarInterface> createBar() final {
        return std::make_unique<BarA>();
    }
};


class FactoryB : public FactoryInterface {
public:
    std::unique_ptr<FooInterface> createFoo() final {
        return std::move(std::make_unique<FooB>());
    }

    std::unique_ptr<BarInterface> createBar() final {
        return std::move(std::make_unique<BarB>());
    }
};


class Application {
    std::unique_ptr<FactoryInterface> m_factory;
    std::unique_ptr<FooInterface> m_foo;
    std::unique_ptr<BarInterface> m_bar;
public:
    explicit Application(std::unique_ptr<FactoryInterface> factory) : m_factory(std::move(factory)) {}

    void setup() {
        m_foo = m_factory->createFoo();
        m_bar = m_factory->createBar();
    }

    void run() {
        m_foo->say_hello();
        m_bar->say_hello();
    }
};


int main() {
    auto factoryA = std::make_unique<FactoryA>();
    auto factoryB = std::make_unique<FactoryB>();

    Application application{ std::move(factoryA) };
    application.setup();
    application.run();

    application = Application{ std::move(factoryB) };
    application.setup();
    application.run();

    return 0;
}

