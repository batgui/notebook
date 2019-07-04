pragma solidity ^0.5.1;
contract rentContract {
    address payable public landlord;
    uint public endTime;
    address public highestTenants;
    uint public highestMoney;
    mapping(address => uint) refundMoney;
    bool end;
    event gethigherMoney(address tenants, uint amount);
    event timeEnd(address winner, uint amount);
    constructor(address payable _landlord, uint _time) public {
            landlord = _landlord;
            endTime = _time + now; 
        }
        
    function tryRent() public payable{
        require(now < endTime, "Time end");
        require(msg.value > highestMoney, "Money not enough");
        
        if (highestMoney != 0) {
            refundMoney[highestTenants] += highestMoney;
        }
        highestTenants = msg.sender;
        highestMoney = msg.value;
        emit gethigherMoney(highestTenants, highestMoney);
    }
    function refund() public returns (bool) {
        require(refundMoney[msg.sender] != 0, "you dont need to refund");
        uint _amount = refundMoney[msg.sender];
        refundMoney[msg.sender] = 0;
        
        if (!msg.sender.send(_amount)) {
            refundMoney[msg.sender] = _amount;
            return false;
            
        }
        return true;
        
    }
    function Endrent() public {
        require(now > endTime, "time's not up");
        require(end == false, "already end");
        end = true;
        emit timeEnd(highestTenants, highestMoney);
        landlord.transfer(highestMoney);
    }
    
}