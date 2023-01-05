#include "Pile.h"

Pile::Pile()
{
    setDeck();
    shuffleCards();
    setPileCards();
    setSpriteTexture();
    setSounds();
}

void Pile::setSounds()
{
    card_click_buffer.loadFromFile("Assets/Sounds/Card Click.wav");
    card_shuffle_buffer.loadFromFile("Assets/Sounds/Card Shuffle.wav");
    card_error_buffer.loadFromFile("Assets/Sounds/Error.wav");
    card_click_sound.setBuffer(card_click_buffer);
    card_shuffle_sound.setBuffer(card_shuffle_buffer);
    card_error_sound.setBuffer(card_error_buffer);
}

void Pile::setDeck()
{
    int index = 0;
    for (int suit = (int)Suits::CLUBS; suit <= (int)Suits::SPADES; ++suit)
    {
        for (int name = (int)CardNames::ACE; name <= (int)CardNames::KING; ++name)
        {
            Card card;
            if (suit == (int)Suits::CLUBS || suit == (int)Suits::SPADES)
            {
                card.color = CardColor::BLACK;
            }
            else
            {
                card.color = CardColor::RED;
            }
            card.name = (CardNames)name;
            card.suit = (Suits)suit;
            card.is_flipped = false;
            card.front_img_file.loadFromFile("Assets/Cards/" + convert_suits[suit - 1] + " - " + convert_names[name - 1] + ".png");
            cards[index] = card;
            ++index;
        }
    }
}

void Pile::shuffleCards()
{
    srand(time(nullptr));
    for (int i = 51; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&cards[i], &cards[j]);
    }
}

void Pile::swap(Card* a, Card* b)
{
    Card temp = *a; 
    *a = *b; 
    *b = temp;
}

void Pile::setXYCoordinates(Card& c)
{
    switch (c.pile)
    {
    case(CardPile::SHUFFLED_PILE):
        c.x_coordinate = 285;
        c.y_coordinate = 118;
        break;
    case(CardPile::DRAW_PILE):
        c.x_coordinate = 0;
        c.y_coordinate = 118;
        break;
    case(CardPile::NORMAL_PILE1):
        c.x_coordinate = 285;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE2):
        c.x_coordinate = 435;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE3):
        c.x_coordinate = 585;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE4):
        c.x_coordinate = 735;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE5):
        c.x_coordinate = 885;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE6):
        c.x_coordinate = 1035;
        c.y_coordinate = 368;
        break;
    case(CardPile::NORMAL_PILE7):
        c.x_coordinate = 1185;
        c.y_coordinate = 368;
        break;
    }
}

void Pile::setPileCards()
{
    for (int i = 0; i < 52; i++)
    {
        if (i == 0)
        {
            cards[i].pile = CardPile::NORMAL_PILE1;
            setXYCoordinates(cards[i]);
            normal_pile1.push_back(cards[i]);
        }
        else if (i >= 1 && i <= 2)
        {
            cards[i].pile = CardPile::NORMAL_PILE2;
            setXYCoordinates(cards[i]);
            normal_pile2.push_back(cards[i]);
        }
        else if (i >= 3 && i <= 5)
        {
            cards[i].pile = CardPile::NORMAL_PILE3;
            setXYCoordinates(cards[i]);
            normal_pile3.push_back(cards[i]);
        }
        else if (i >= 6 && i <= 9)
        {
            cards[i].pile = CardPile::NORMAL_PILE4;
            setXYCoordinates(cards[i]);
            normal_pile4.push_back(cards[i]);
        }
        else if (i >= 10 && i <= 14)
        {
            cards[i].pile = CardPile::NORMAL_PILE5;
            setXYCoordinates(cards[i]);
            normal_pile5.push_back(cards[i]);
        }
        else if (i >= 15 && i <= 20)
        {
            cards[i].pile = CardPile::NORMAL_PILE6;
            setXYCoordinates(cards[i]);
            normal_pile6.push_back(cards[i]);
        }
        else if (i >= 21 && i <= 27)
        {
            cards[i].pile = CardPile::NORMAL_PILE7;
            setXYCoordinates(cards[i]);
            normal_pile7.push_back(cards[i]);
        }
        else
        {
            cards[i].pile = CardPile::SHUFFLED_PILE;
            setXYCoordinates(cards[i]);
            shuffled_pile.push(cards[i]);
            setSpriteTexture(1);
        }
    }
}

void Pile::setSpriteTexture()
{
    setSpriteTexture(normal_pile1);
    setSpriteTexture(normal_pile2);
    setSpriteTexture(normal_pile3);
    setSpriteTexture(normal_pile4);
    setSpriteTexture(normal_pile5);
    setSpriteTexture(normal_pile6);
    setSpriteTexture(normal_pile7);
}

void Pile::setSpriteTexture(vector<Card>& pile)
{
    for (int i = 0; i < pile.size(); ++i)
    {
        pile.at(i).card_sprite.setTexture(pile.at(i).back_img_file);
        pile.at(i).card_sprite.setPosition(pile.at(i).x_coordinate, pile.at(i).y_coordinate + (i * offset));

        if (i == pile.size() - 1)
        {
            pile.at(i).card_sprite.setTexture(pile.at(i).front_img_file);
            pile.at(i).card_sprite.setPosition(pile.at(i).x_coordinate, pile.at(i).y_coordinate + (i * offset));
            pile.at(i).is_flipped = true;
        }
    }
}

void Pile::setSpriteTexture(int pile_number)
{
    switch (pile_number)
    {
    case 1: // Shuffle pile
        shuffled_pile.top().card_sprite.setTexture(shuffled_pile.top().back_img_file);
        shuffled_pile.top().card_sprite.setPosition(shuffled_pile.top().x_coordinate, shuffled_pile.top().y_coordinate);
        shuffled_pile.top().is_flipped = false;
        break;
    case 2: // Draw pile
        draw_pile.top().card_sprite.setTexture(draw_pile.top().front_img_file);
        draw_pile.top().card_sprite.setPosition(draw_pile.top().x_coordinate + 180, draw_pile.top().y_coordinate);
        draw_pile.top().is_flipped = true;
        break;
    case 3: // Foundation pile 1
        foundation_pile1.top().card_sprite.setTexture(foundation_pile1.top().front_img_file);
        foundation_pile1.top().x_coordinate = 740;
        foundation_pile1.top().y_coordinate = 119;
        foundation_pile1.top().card_sprite.setPosition(foundation_pile1.top().x_coordinate, foundation_pile1.top().y_coordinate);
        break;
    case 4: // Foundation pile 2
        foundation_pile2.top().card_sprite.setTexture(foundation_pile2.top().front_img_file);
        foundation_pile2.top().x_coordinate = 890;
        foundation_pile2.top().y_coordinate = 119;
        foundation_pile2.top().card_sprite.setPosition(foundation_pile2.top().x_coordinate, foundation_pile2.top().y_coordinate);
        break;
    case 5: // Foundation pile 3
        foundation_pile3.top().card_sprite.setTexture(foundation_pile3.top().front_img_file);
        foundation_pile3.top().x_coordinate = 1040;
        foundation_pile3.top().y_coordinate = 119;
        foundation_pile3.top().card_sprite.setPosition(foundation_pile3.top().x_coordinate, foundation_pile3.top().y_coordinate);
        break;
    case 6: // Foundation pile 4
        foundation_pile4.top().card_sprite.setTexture(foundation_pile4.top().front_img_file);
        foundation_pile4.top().x_coordinate = 1190;
        foundation_pile4.top().y_coordinate = 119;
        foundation_pile4.top().card_sprite.setPosition(foundation_pile4.top().x_coordinate, foundation_pile4.top().y_coordinate);
        break;
    case 7: // Normal pile 1
        for (int i = 0; i < normal_pile1.size(); ++i)
        {
            if (normal_pile1[i].is_flipped == true)
            {
                normal_pile1[i].card_sprite.setTexture(normal_pile1[i].front_img_file);
                normal_pile1[i].x_coordinate = 285;
                normal_pile1[i].y_coordinate = 368;
                normal_pile1[i].card_sprite.setPosition(normal_pile1[i].x_coordinate, normal_pile1[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile1[i].card_sprite.setTexture(normal_pile1[i].back_img_file);
                normal_pile1[i].x_coordinate = 285;
                normal_pile1[i].y_coordinate = 368;
                normal_pile1[i].card_sprite.setPosition(normal_pile1[i].x_coordinate, normal_pile1[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 8: // Normal pile 2
        for (int i = 0; i < normal_pile2.size(); ++i)
        {
            if (normal_pile2[i].is_flipped == true)
            {
                normal_pile2[i].card_sprite.setTexture(normal_pile2[i].front_img_file);
                normal_pile2[i].x_coordinate = 435;
                normal_pile2[i].y_coordinate = 368;
                normal_pile2[i].card_sprite.setPosition(normal_pile2[i].x_coordinate, normal_pile2[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile2[i].card_sprite.setTexture(normal_pile2[i].back_img_file);
                normal_pile2[i].x_coordinate = 435;
                normal_pile2[i].y_coordinate = 368;
                normal_pile2[i].card_sprite.setPosition(normal_pile2[i].x_coordinate, normal_pile2[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 9: // Normal pile 3
        for (int i = 0; i < normal_pile3.size(); ++i)
        {
            if (normal_pile3[i].is_flipped == true)
            {
                normal_pile3[i].card_sprite.setTexture(normal_pile3[i].front_img_file);
                normal_pile3[i].x_coordinate = 585;
                normal_pile3[i].y_coordinate = 368;
                normal_pile3[i].card_sprite.setPosition(normal_pile3[i].x_coordinate, normal_pile3[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile3[i].card_sprite.setTexture(normal_pile3[i].back_img_file);
                normal_pile3[i].x_coordinate = 585;
                normal_pile3[i].y_coordinate = 368;
                normal_pile3[i].card_sprite.setPosition(normal_pile3[i].x_coordinate, normal_pile3[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 10: // Normal pile 4
        for (int i = 0; i < normal_pile4.size(); ++i)
        {
            if (normal_pile4[i].is_flipped == true)
            {
                normal_pile4[i].card_sprite.setTexture(normal_pile4[i].front_img_file);
                normal_pile4[i].x_coordinate = 735;
                normal_pile4[i].y_coordinate = 368;
                normal_pile4[i].card_sprite.setPosition(normal_pile4[i].x_coordinate, normal_pile4[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile4[i].card_sprite.setTexture(normal_pile4[i].back_img_file);
                normal_pile4[i].x_coordinate = 735;
                normal_pile4[i].y_coordinate = 368;
                normal_pile4[i].card_sprite.setPosition(normal_pile4[i].x_coordinate, normal_pile4[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 11: // Normal pile 5
        for (int i = 0; i < normal_pile5.size(); ++i)
        {
            if (normal_pile5[i].is_flipped == true)
            {
                normal_pile5[i].card_sprite.setTexture(normal_pile5[i].front_img_file);
                normal_pile5[i].x_coordinate = 885;
                normal_pile5[i].y_coordinate = 368;
                normal_pile5[i].card_sprite.setPosition(normal_pile5[i].x_coordinate, normal_pile5[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile5[i].card_sprite.setTexture(normal_pile5[i].back_img_file);
                normal_pile5[i].x_coordinate = 885;
                normal_pile5[i].y_coordinate = 368;
                normal_pile5[i].card_sprite.setPosition(normal_pile5[i].x_coordinate, normal_pile5[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 12: // Normal pile 6
        for (int i = 0; i < normal_pile6.size(); ++i)
        {
            if (normal_pile6[i].is_flipped == true)
            {
                normal_pile6[i].card_sprite.setTexture(normal_pile6[i].front_img_file);
                normal_pile6[i].x_coordinate = 1035;
                normal_pile6[i].y_coordinate = 368;
                normal_pile6[i].card_sprite.setPosition(normal_pile6[i].x_coordinate, normal_pile6[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile6[i].card_sprite.setTexture(normal_pile6[i].back_img_file);
                normal_pile6[i].x_coordinate = 1035;
                normal_pile6[i].y_coordinate = 368;
                normal_pile6[i].card_sprite.setPosition(normal_pile6[i].x_coordinate, normal_pile6[i].y_coordinate + (offset * i));
            }
        }
        break;
    case 13: // Normal pile 7
        for (int i = 0; i < normal_pile7.size(); ++i)
        {
            if (normal_pile7[i].is_flipped == true)
            {
                normal_pile7[i].card_sprite.setTexture(normal_pile7[i].front_img_file);
                normal_pile7[i].x_coordinate = 1185;
                normal_pile7[i].y_coordinate = 368;
                normal_pile7[i].card_sprite.setPosition(normal_pile7[i].x_coordinate, normal_pile7[i].y_coordinate + (offset * i));
            }
            else
            {
                normal_pile7[i].card_sprite.setTexture(normal_pile7[i].back_img_file);
                normal_pile7[i].x_coordinate = 1185;
                normal_pile7[i].y_coordinate = 368;
                normal_pile7[i].card_sprite.setPosition(normal_pile7[i].x_coordinate, normal_pile7[i].y_coordinate + (offset * i));
            }
        }
        break;
    }
}

void Pile::displayCards(RenderWindow& window)
{
    displayCards(window, shuffled_pile);
    displayCards(window, draw_pile);
    displayCards(window, foundation_pile1);
    displayCards(window, foundation_pile2);
    displayCards(window, foundation_pile3);
    displayCards(window, foundation_pile4);
    displayCards(window, normal_pile1, 7);
    displayCards(window, normal_pile2, 8);
    displayCards(window, normal_pile3, 9);
    displayCards(window, normal_pile4, 10);
    displayCards(window, normal_pile5, 11);
    displayCards(window, normal_pile6, 12);
	displayCards(window, normal_pile7, 13);
}

void Pile::displayCards(RenderWindow& window, stack<Card>& stack)
{
    for (int i = 0; i < stack.size(); i++) // Draw pile
        window.draw(stack.top().card_sprite);
}

void Pile::displayCards(RenderWindow& window, vector<Card>& pile, int pile_number)
{
    for (int i = 0; i < pile.size(); i++) // Normal pile 1
    {
        setSpriteTexture(pile_number);
        window.draw(pile[i].card_sprite);
    }
}

void Pile::checkIfSpriteIsClicked(Vector2f mouse) 
{
    FloatRect bounds;

    // Draw Pile
    if (!draw_pile.empty())
        bounds = draw_pile.top().card_sprite.getGlobalBounds();
    if (bounds.contains(mouse)) {
        moveCard(1, foundation_pile1, normal_pile1, 0);
        return;
    }

    if (!foundation_pile1.empty())
        bounds = foundation_pile1.top().card_sprite.getGlobalBounds();
    if (bounds.contains(mouse)) {
        moveCard(2, foundation_pile1, normal_pile1, 0);
        return;
    }
    if (!foundation_pile2.empty())
        bounds = foundation_pile2.top().card_sprite.getGlobalBounds();
    if (bounds.contains(mouse)) {
        moveCard(2, foundation_pile2, normal_pile1, 0);
        return;
    }
    if (!foundation_pile3.empty())
        bounds = foundation_pile3.top().card_sprite.getGlobalBounds();
    if (bounds.contains(mouse)) {
        moveCard(2, foundation_pile3, normal_pile1, 0);
        return;
    }
    if (!foundation_pile4.empty())
        bounds = foundation_pile4.top().card_sprite.getGlobalBounds();
    if (bounds.contains(mouse)) {
        moveCard(2, foundation_pile4, normal_pile1, 0);
        return;
    }
    for (int i = normal_pile1.size() - 1; i >= 0; i--) {
        bounds = normal_pile1[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile1[i].is_flipped)
        {
            moveCard(3, foundation_pile1, normal_pile1, i);
            return;
        }
    }
    for (int i = normal_pile2.size() - 1; i >= 0; i--) {
        bounds = normal_pile2[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile2[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile2, i);
            return;
        }
    }
    for (int i = normal_pile3.size() - 1; i >= 0; i--) {
        bounds = normal_pile3[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile3[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile3, i);
            return;
        }
    }
    for (int i = normal_pile4.size() - 1; i >= 0; i--) {
        bounds = normal_pile4[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile4[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile4, i);
            return;
        }
    }
    for (int i = normal_pile5.size() - 1; i >= 0; i--) {
        bounds = normal_pile5[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile5[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile5, i);
            return;
        }
    }
    for (int i = normal_pile6.size() - 1; i >= 0; i--) {
        bounds = normal_pile6[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile6[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile6, i);
            return;
        }
    }
    for (int i = normal_pile7.size() - 1; i >= 0; i--) {
        bounds = normal_pile7[i].card_sprite.getGlobalBounds();
        if (bounds.contains(mouse) && normal_pile7[i].is_flipped) {
            moveCard(3, foundation_pile1, normal_pile7, i);
            return;
        }
    }
}

void Pile::moveCard(int pile_number, stack<Card>& fPile, vector<Card>& nPile, int index)
{
    switch (pile_number)
    {
    case 1: // Draw Pile
        moveFromDrawPile();
        return;
    case 2: // Foundation Pile
        moveFromFoundationPile(fPile);
        return;
    case 3: // Normal Pile
        moveFromNormalPile(nPile, index);
        return;
    }
}

void Pile::moveFromShuffledPile()
{
    if (!shuffled_pile.empty())
    {
        card_click_sound.play();
        draw_pile.push(shuffled_pile.top());
        shuffled_pile.pop();
        setSpriteTexture(2);
    }
    else
    {
        while (!draw_pile.empty())
        {
            card_shuffle_sound.play();
            shuffled_pile.push(draw_pile.top());
            draw_pile.pop();
            setSpriteTexture(1);
        }
    }
}

void Pile::moveFromDrawPile()
{
    if (moveFromDrawPile(foundation_pile1, 3))
        return;
    if (moveFromDrawPile(foundation_pile2, 4))
        return;
    if (moveFromDrawPile(foundation_pile3, 5))
        return;
    if (moveFromDrawPile(foundation_pile4, 6))
        return;
    if (moveFromDrawPile(normal_pile1, 7))
        return;
    if (moveFromDrawPile(normal_pile2, 8))
        return;
    if (moveFromDrawPile(normal_pile3, 9))
        return;
    if (moveFromDrawPile(normal_pile4, 10))
        return;
	if (moveFromDrawPile(normal_pile5, 11))
		return;
	if (moveFromDrawPile(normal_pile6, 12))
		return;
	if (moveFromDrawPile(normal_pile7, 13))
		return;
    
    card_error_sound.play();
    return;
}

bool Pile::moveFromDrawPile(stack<Card>& stack, int pile_number)
{
    if (stack.empty() && int(draw_pile.top().name) == 1 || (!stack.empty() && int(stack.top().color) == int(draw_pile.top().color)
            && int(stack.top().suit) == int(draw_pile.top().suit) && (int(stack.top().name) - int(draw_pile.top().name) == -1)))
    {
        card_click_sound.play();
        stack.push(draw_pile.top());
        draw_pile.pop();
        setSpriteTexture(pile_number);
        return true;
    }
    return false;
}

bool Pile::moveFromDrawPile(vector<Card>& pile, int pile_number)
{
    if (pile.empty() && int(draw_pile.top().name) == 13 || (!pile.empty()
            && int(pile.back().color) != int(draw_pile.top().color) && (int(pile.back().name) - int(draw_pile.top().name) == 1)))
    {
        card_click_sound.play();
        pile.push_back(draw_pile.top());
        draw_pile.pop();
        setSpriteTexture(pile_number);
        return true;
    }
    return false;
}

void Pile::moveFromFoundationPile(stack<Card>& pile)
{
    if (moveFromFoundationPile(foundation_pile1, pile, 3))
        return;
    if (moveFromFoundationPile(foundation_pile2, pile, 4))
        return;
    if (moveFromFoundationPile(foundation_pile3, pile, 5))
        return;
    if (moveFromFoundationPile(foundation_pile4, pile, 6))
        return;
    if (moveFromFoundationPile(normal_pile1, pile, 7))
        return;
    if (moveFromFoundationPile(normal_pile2, pile, 8))
        return;
    if (moveFromFoundationPile(normal_pile3, pile, 9))
        return;
    if (moveFromFoundationPile(normal_pile4, pile, 10))
        return;
    if (moveFromFoundationPile(normal_pile5, pile, 11))
        return;
    if (moveFromFoundationPile(normal_pile6, pile, 12))
        return;
    if (moveFromFoundationPile(normal_pile7, pile, 13))
        return;
    
    card_error_sound.play();
    return;
}

bool Pile::moveFromFoundationPile(stack<Card>& foundation, stack<Card>& pile, int pile_number)
{
    if (foundation.empty() && int(pile.top().name) == 1)
    {
        card_click_sound.play();
        foundation.push(pile.top());
        pile.pop();
        setSpriteTexture(pile_number);
        return true;
    }
    return false;
}

bool Pile::moveFromFoundationPile(vector<Card>& nPile, stack<Card>& pile, int pile_number)
{
    if (int(nPile.back().color) != int(pile.top().color) \
		&& (int(nPile.back().name) - int(pile.top().name) == 1))
	{
			card_click_sound.play();
            nPile.push_back(pile.top());
			pile.pop();
			setSpriteTexture(pile_number);
			return true;
    }
    return false;
}

void Pile::moveFromNormalPile(vector<Card>& pile, int index)
{
    if (moveFromNormalPile(foundation_pile1, pile, 3, index))
        return;
    if (moveFromNormalPile(foundation_pile2, pile, 4, index))
        return;
    if (moveFromNormalPile(foundation_pile3, pile, 5, index))
        return;
    if (moveFromNormalPile(foundation_pile4, pile, 6, index))
        return;
    if (moveFromNormalPile(normal_pile1, pile, 7, index))
        return;
    if (moveFromNormalPile(normal_pile2, pile, 8, index))
        return;
    if (moveFromNormalPile(normal_pile3, pile, 9, index))
        return;
    if (moveFromNormalPile(normal_pile4, pile, 10, index))
        return;
    if (moveFromNormalPile(normal_pile5, pile, 11, index))
        return;
    if (moveFromNormalPile(normal_pile6, pile, 12, index))
        return;
    if (moveFromNormalPile(normal_pile7, pile, 13, index))
        return;

    card_error_sound.play();
    return;
}

bool Pile::moveFromNormalPile(stack<Card>& foundation, vector<Card>& pile, int pile_number, int index)
{
    if (foundation.empty() && int(pile.at(index).name) == 1
        || (!foundation.empty()
            && int(foundation.top().color) == int(pile.at(index).color)
            && int(foundation.top().suit) == int(pile.at(index).suit)
            && (int(foundation.top().name) - int(pile.at(index).name) == -1)))
    {
        card_click_sound.play();
        foundation.push(pile.at(index));
        pile.pop_back();
        if (!pile.empty())
            pile.back().is_flipped = true;
        setSpriteTexture(pile_number);
        return true;
    }
    return false;
}

bool Pile::moveFromNormalPile(vector<Card>& nPile, vector<Card>& pile, int pile_number, int index)
{
    if (nPile.empty() && int(pile.at(index).name) == 13
        || (!nPile.empty()
            && int(nPile.back().color) != int(pile.at(index).color)
            && (int(nPile.back().name) - int(pile.at(index).name) == 1))) // Normal Pile 1
    {
        card_click_sound.play();
        for (int i = index; i < pile.size(); ++i)
            nPile.push_back(pile[i]);
        pile.erase(pile.begin() + index, pile.end());
        if (!pile.empty())
            pile.back().is_flipped = true;
        setSpriteTexture(pile_number);
        return true;
    }
    return false;
}

bool Pile::gameWon()
{
    if (!foundation_pile1.empty() && int(foundation_pile1.top().name) == 13)
        if (!foundation_pile2.empty() && int(foundation_pile2.top().name) == 13)
            if (!foundation_pile3.empty() && int(foundation_pile3.top().name) == 13)
                if (!foundation_pile4.empty() && int(foundation_pile4.top().name) == 13)
                    return true;
    return false;
}
