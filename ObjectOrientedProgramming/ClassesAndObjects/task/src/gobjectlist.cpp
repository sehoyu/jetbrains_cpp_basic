#include "gobjectlist.hpp"

void GameObjectList::link(GameObjectList::Node *cursor, std::unique_ptr<Node> &&node) {
    if (!cursor || !node) return;

    node->prev = cursor;
    node->next = std::move(cursor->next);
    if (node->next) {
        node->next->prev = node.get();
    }
    cursor->next = std::move(node);
}

void GameObjectList::unlink(GameObjectList::Node *node) {
    if (!node || !node->prev || !node->next) return;

    node->next->prev = node->prev;
    node->prev->next = std::move(node->next);
}

GameObjectList::GameObjectList() {
    head = std::make_unique<Node>();             // 1. [노드 A] 생성 (head가 소유)
    auto tailNode = std::make_unique<Node>();    // 2. [노드 B] 생성 (tailNode가 임시 소유)
    link(head.get(), std::move(tailNode));       // 3. [노드 A] 뒤에 [노드 B]를 연결
    tail = head->next.get();                     // 4. tail 포인터가 [노드 B]를 가리키게 함
}

void GameObjectList::insert(const std::shared_ptr<GameObject> &object) {
    if (!object) {
        return;
    }
    std::unique_ptr<Node> temp = std::make_unique<Node>();
    temp->object = object;
    link(tail->prev, std::move(temp));
}

void GameObjectList::remove(const std::function<bool(const GameObject &)> &pred) {
    GameObjectList::Node* curr = head->next.get();
    while (curr != tail) {
        Node* next = curr->next.get();
        if (pred(*curr->object)) {
            unlink(curr);
        }
        curr = next;
    }
}

void GameObjectList::foreach(const std::function<void (GameObject&)>& apply) {
    Node* curr = head->next.get();
    while (curr != tail) {
        apply(*curr->object);
        curr = curr->next.get();
    }
}

void GameObjectList::foreach(const std::function<void (const GameObject&)>& apply) const {
    Node* curr = head->next.get();
    while (curr != tail) {
        apply(*curr->object);
        curr = curr->next.get();
    }
}

GameObjectList::GameObjectList(const GameObjectList &other) : GameObjectList() {
    head = std::make_unique<Node>();
    std::unique_ptr<Node> temp = std::make_unique<Node>();
    link(head.get(), std::move(temp));
    tail = head->next.get();

    Node* curr = other.head->next.get();
    while (curr != other.tail) {
        this->insert(curr->object);
        curr = curr->next.get();
    }
}

GameObjectList::GameObjectList(GameObjectList &&other) noexcept : GameObjectList() {
    swap(*this, other);
}

GameObjectList &GameObjectList::operator=(GameObjectList other) {
    swap(*this, other);
    return *this;
}

void swap(GameObjectList& first, GameObjectList& second) {
    using std::swap;
    swap(first.head, second.head);
    swap(first.tail, second.tail);
}
