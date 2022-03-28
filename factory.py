from __future__ import annotations
from abc import ABC, abstractmethod

class MyObject(ABC):

    @abstractmethod
    def foo(self) -> None:
        pass

    @abstractmethod
    def bar(self) -> None:
        pass

    @abstractmethod
    def say_hello(self, name: str) -> None:
        pass

class ObjectA(MyObject):

    def foo(self) -> None:
        print("ObjectA::foo")

    def bar(self) -> None:
        print("ObjectA::bar")

    def say_hello(self, name: str) -> None:
        print(f"ObjectA::say_hello {name}")

class ObjectB(MyObject):

    def foo(self) -> None:
        print("ObjectB::foo")

    def bar(self) -> None:
        print("ObjectB::bar")
    
    def say_hello(self, name: str) -> None:
        print(f"ObjectB::say_hello {name}")

class Factory(ABC):
    @abstractmethod
    def make_object(self) -> MyObject:
        pass
    
    def run(self) -> None:
        obj = self.make_object()
        obj.foo()
        obj.bar()
        obj.say_hello("Albert")

class FactoryA(Factory):
    def make_object(self) -> ObjectA:
        return ObjectA()

class FactoryB(Factory):
    def make_object(self) -> ObjectB:
        return ObjectB()

def main():
    factoryA = FactoryA()
    factoryA.run()

    factoryB = FactoryB()
    factoryB.run()

if __name__ == "__main__":
    main()
