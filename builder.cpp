#include <iostream>
#include <memory>

class ObjectA {

};

class ObjectB {

};

template<typename T>
class Builder {
public:
    virtual void reset() = 0;
    virtual std::unique_ptr<T> getResult() = 0;
    virtual void method1() = 0;
    virtual void method2() = 0;
    virtual void method3() = 0;
};

class ObjectABuilder : public Builder<ObjectA> {
private:
    std::unique_ptr<ObjectA> m_object = std::make_unique<ObjectA>();

public:
    void reset() final {
        m_object.reset();
        m_object = std::make_unique<ObjectA>();
    }

    std::unique_ptr<ObjectA> getResult() final {
        return std::move(m_object);
    }

    void method1() final {
        std::cout << "ObjectA Method1\n";
    }

    void method2() final {
        std::cout << "ObjectA Method2\n";
    }

    void method3() final {
        std::cout << "ObjectA Method3\n";
    }
};

class ObjectBBuilder : public Builder<ObjectB> {
private:
    std::unique_ptr<ObjectB> m_object = std::make_unique<ObjectB>();

public:
    void reset() final {
        m_object.reset();
        m_object = std::make_unique<ObjectB>();
    }

    std::unique_ptr<ObjectB> getResult() final {
        return std::move(m_object);
    }

        void method1() final {
        std::cout << "ObjectB Method1\n";
    }

    void method2() final {
        std::cout << "ObjectB Method2\n";
    }

    void method3() final {
        std::cout << "ObjectB Method3\n";
    }

};

class Director {
public:
    template <typename T>
    std::unique_ptr<T> makeVariantA(Builder<T> &builder) {
        builder.reset();
        builder.method1();
        builder.method2();
        return builder.getResult();
    }

    template <typename T>
    std::unique_ptr<T> makeVariantB(Builder<T> &builder) {
        builder.reset();
        builder.method1();
        builder.method2();
        builder.method3();
        return builder.getResult();
    }
};

int main() {
    Director director{};
    ObjectABuilder objectABuilder{};
    auto objectA_A = director.makeVariantA<ObjectA>(objectABuilder);
    auto objectA_B = director.makeVariantB<ObjectA>(objectABuilder);

    ObjectBBuilder ObjectBBuilder{};
    auto objectB_A = director.makeVariantA<ObjectB>(ObjectBBuilder);
    auto objectB_B = director.makeVariantB<ObjectB>(ObjectBBuilder);

    return 0;
}