#include <Market.h>

Market::Market(int32_t pointIdx, int32_t postIdx, uint32_t productCapacity, uint32_t replenishment,
               uint32_t product, std::string name) :
               Node(pointIdx, postIdx, Market::TYPE),
               name_(std::move(name)),
               productCapacity_(productCapacity),
               product_(product),
               replenishment_(replenishment) {
    product_ = product;
}

uint32_t Market::getProductCapacity() const {
    return productCapacity_;
}

uint32_t Market::getReplenishment() const {
    return replenishment_;
}

uint32_t Market::getProduct() const {
    return product_;
}

const std::string& Market::getName() const {
    return name_;
}

void Market::setProduct(uint32_t product) {
    product_ = product;
}
