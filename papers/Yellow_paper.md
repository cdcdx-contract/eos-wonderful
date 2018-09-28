# EOS-Wonderful 황서
작성자: 김선태, 블록체인/데이터 팀
2018년 9월 20일
# 프로젝트 요약 - EOS-Wonderful

## 목적
블록체인을 이용하여 실생활에 사용 가능한 댑을 제작하기엔 현재의 블록체인 기술 수준이 부족합니다. 첫번째로, 계정 생성과 자원 할당에 들어가는 비용의 부담이 큽니다. 두번째로, 비용이 해결되더라도, 접근성 면에서 한계가 있습니다. 사용자 경험이 매우 안좋아집니다. 세번째로, 위의 문제를 해결하기 위해서 프라이빗 체인을 구성하는것은 해결책이 아닙니다.

EOS-Wonderful을 이용해 위의 문제들을 해결하고, 실생활에 사용 가능한 진짜 댑을 만들 수 있는 솔루션을 제시합니다.
## 목표
퍼블릭 체인에서, 탈중앙성을 포기하지 않고도 높은 접근성과 낮은 비용을 달성해야합니다. 첫번째, 퍼블릭 체인 위에서 제공돼야합니다. 두번째, 유저당 들어가는 비용을 최소화 해야합니다. 세번째, 접근성을 높히기 위한 클라이언트 SDK가 완성돼야합니다. 네번째, 탈중앙성과 접근성 유지를 위해 서버 SDK가 완성돼야 합니다. 다섯번째, 모든 소스를 깃헙에 오픈하고 라이센스를 설정하여 비영리성 사용 및 접근을 열어두어 개발자들에게 열린 환경을 제공해 주어야 합니다. 이는 궁극적으로 EOS-Wonderful을 업그레이드 시켜줄것입니다.
## 솔루션
비용 절감을 위해 계정 생성을 하지 않습니다. 하나의 계정을 모두가 공유하기 때문에 자원도 효율적으로 사용됩니다. 하나의 계정을 공유하면서 생기는 문제를 해결하기 위해 이중 검증을 통해 사용자를 구별합니다. 이중검증은 EOS-Wonderful 계정내에 스마트컨트랙으로 구현되어 있습니다.
## 프로젝트 개요
### 문제점
 EOS-Wonderful은 실생활에 사용이 가능한 퍼블릭 체인 기반의 댑 운영을 위해 구상되고 제작되었습니다.

이오스 메인넷을 사용하기 위해서 사용자는 이오스 계정이 필요합니다. 이오스 계정을 생성하기 위해서는 이미 계정이 있는 사람이 약 2천원 가량의 비용을 지불해야 합니다. 옆에 사진과 같이, 이오스의 가격은 현재 약 6370원이고, 계정 생성에 필요한 3200 byte의 램이 약 0.3 EOS로 제일 많은양을 차지하고, 10회 전송이 가능한 자원을 할당하는데에 약 0.04 EOS 정도 추가 비용이 들어갑니다. 총 0.34 EOS 가량 소모되며, 원화로는 2135원 입니다. 자원 평균 사용률이 10%인 경우 EOS-Wonderful을 적용하면 램 사용률은 3200Byte->203Byte로 줄고, 자원 할당에 필요한 금액은 0.04EOS -> 0.004EOS 로 줄기 때문에 총 145원의 돈이 필요하게 됩니다.

 또한, 이오스 네트워크에 부하가 없다는 전제하에서, 계정이 자원을 얻기 위해서는 적지 않은 돈을 “홀딩”해야 합니다. “홀딩”된 돈을 회수하기 위해서는 최소 3일 이상이 소요되며, 수차례 전송하는 수준의 많은 자원을 소모하기 때문에 홀딩되는 자원의 유동성을 확보하기 어렵습니다.
 
 서비스 운영시 대부분의 계정은 휴면 계정으로서 대부분의 홀딩된 금액은 사용하지 않는 잉여 자원이 되어버립니다. 그외에 서비스를 이용하는 비휴면 고객은 자원이 부족한 상황이 생기게 됩니다.

 즉, 매우 높은 계정 생성비와 비효율적인 자원 할당으로 인한 낭비, 그리고 계정을 생성하고 사용할 때 부딪히는 접근성 난이도 문제는 실생활에 사용되는 댑을 만들 때 큰 걸림돌이 됩니다.

### 용어정리
**이중검증** - 계정을 공유하는 다수의 사용자를 식별할 수 있도록 한 차례 더 서명 검증을 거치는 방법, EOS-Wonderful(이하 E-W)의 핵심 기능
**E-W 스마트컨트랙** - 이중검증 및 사용자 데이터 관리 기능과 댑 관련 기능이 포함되어 있는 스마트컨트랙트 코드
**E-W 계정** - E-W 스마트컨트랙이 적용된 이오스 계정, 탈중앙화가 가능하지만 기본값인 경우 계정의 소유주가 관리 및 설정 권한을 가짐
**서버 계정** - 계정이 없는 사용자에게 자원을 빌려주는 계정, 안쓰는 자원을 소모하고 보상으로 수수료를 받음
**클라이언트 SDK** - 사용자 어플리케이션이 서버 계정을 통해 E-W계정과 통신하기 위한 기능을 가진 개발 키트
**서버 SDK** - 클라이언트 SDK가 소모할 자원을 가진 계정을 빌려 주기 위한 개발키트

### 개요
 EOS-Wonderful을 이용하면, 계정이 없는 사용자도 댑을 이용할 수 있게 됩니다. EOS-Wonderful 계정에서 모든 사용자의 정보가 관리되지만, 해당 계정은 탈중앙화되어 있으며 스마트컨트랙 이중검증을 통해 사용자를 식별함으로써 보안 문제가 생기지 않으며 기존의 계정을 사용하는것과 동일한 탈중앙성이 보장됩니다. Eos-Wonderful 계정의 자원이 모두 소모되거나 계정 제공 서버가 Down 되는 경우에도, 다른 이오스 계정, 혹은 이오스 계정이 있는 제 3자가 오픈된 서버 SDK를 이용하여 즉시 서비스를 재개할 수 있으며, 이 경우에도 보안 및 탈중앙성이 손상되지 않습니다. 개인의 식별은 트랜잭션의 생성자가 아닌 이중검증을 통해 진행되기 때문입니다. 결과적으로, 이오스 체인이 유지되는 한 EOS-Wonderful은  접근성/탈중앙성/보안성/무결성이 지속됩니다.

 EOS-Wonderful의 주요 구성 요소는 크게 이중검증/접근성/SDK 3가지로 나눌 수 있습니다. 

### 이중검증
 이중검증을 설명하기 전에, 이오스의 트랜잭션 검증이 어떻게 이루어지는 지 설명하겠습니다. 이오스에서 트랜잭션을 생성하기 위해선 우선 목표하는 행위와 계정을 이용하여 액션을 생성합니다. 이렇게 만들어진 하나 이상의 액션을 트랜잭션에 담고, 트랜잭션 내부의 모든 데이터를 계정의 공개키와 매칭되는 개인키로 서명하여 트래잭션에 포함시켜 전송합니다. 이후 노드들은 트랜잭션에 적힌 계정명의 공개키로 서명을 해제하여 본인임을 확인합니다. 
 
 여기서 서명 정보는 트랜잭션 가장 외부에 기록되어 있습니다. 이 부분에서 이중검증과 차이가 있습니다. 이중검증은 트랜잭션의 서명이 정상인 경우, 트랜잭션 안의, 액션 안의, 데이터 안에 적힌 공개키 정보와 서명 정보를 이용해 개인을 식별하게 됩니다. 즉 개인을 식별함에 있어서 해당 트랜잭션을 발생시킨 계정이 무엇인지는 전혀 상관이 없으며, 오직 데이터안의 서명 정보만으로 개인을 식별하기 때문에 하나의 계정을 여럿이 공유하는것이 가능합니다.

### 접근성
 접근성은 아주 중요한 요소 중 하나입니다. 계정을 생성하는 중간 과정을 제외하고, 계정없이 사용하기 위해서 EOS-Wonderful은 이더리움과 비슷한 키-계정 방식을 이용합니다. 공개키 자체가 계정이 되는것입니다. 
 
 즉각적인 계정의 조회를 위해 공개키의 앞 28비트를 정수형으로 변환하여 인덱스 키로 사용합니다. 그덕에 사용자는 자신의 키-계정 데이터를 즉시 조회할 수 있습니다. 만약 이런 설계가 없는 경우에는 사용자가 자신의 데이터를 조회하거나 다른 사람에게 입금하기 위해서는 EOS-Wonderful 계정을 사용하는 모든 사람의 계정 정보를 전부 조회하고, 자신과 대상의 키를 대조해서 찾아야 합니다. 이덕에 이오스를 처음 사용하는 사용자도 중간 단계없이 키쌍 하나로 입금/조회/송금 및 그외에 모든 행위가 즉시 가능해집니다.

### SDK
 SDK는 EOS-wonderful 프로토콜에 맞춰 제작된 툴킷으로서, 댑을 만들거나 제공하기 위해 꼭 필요합니다. 기본적으로, 이중검증된 액션을 생성하기 위해서는 스마트컨트랙의 서명 검증 방식에 대응되는 서명을 생성 해야합니다. 이중검증은 특이한 구조를 지니기 때문에 replay-attack에 잠재적인 취약성을 갖습니다. 이것을 해결하기 위해 Account-state nonce 개념이 도입되어 있어 트랜잭션 생성 과정이 한 층 더 복잡합니다. 
 
 클라이언트 SDK는 이것을 모두 자동으로 진행하여 액션을 생성해줍니다. 또한 서버 SDK와 통신하여 타인의 계정을 빌려 트랜잭션을 생성해 전파하고 서비스를 이용하게 됩니다. 서버 SDK는 실제로 트랜잭션을 생성하는대에 자원을 소모하는 계정을 사용자에게 제공하기 위해 필요합니다. 클라이언트는 서버SDK가 적용된 서버에 연결해 자신이 생성한 액션을 실제 계정의 자원을 이용하여 트랜잭션화-전송하게 됩니다. 
 
 동시에 서버 SDK는 탈중앙성의 가장 중요한 요소인 구조적 탈중앙화를 유지하고 서비스의 영속을 유지하기 위해 필요합니다. EOS-Wonderful에서 실제 자원을 소모하는것은 트랜잭션을 생성하는 서버 계정입니다. 그리고 이 계정과 계정에 할당된 자원은 보통 댑을 제공하는 회사에서 구비하게 됩니다. 
 
 여기서 문제가 생깁니다. “댑을 제공하는 회사”가 계정의 자원을 확보하지 않거나 서버 계정을 Down시켜 탈중앙화 시킨 스마트컨트랙 기반의 서비스를 임의로 중단할 수 있습니다. 하지만 이 경우 이오스 계정을 가진 사람은 누구든지 자신의 계정과 자동화된 서버 SDK를 이용해 서비스를 재개할 수 있습니다. 
 
 서비스를 제공함으로서 소모되는 자원은 EOS-Wonderful 수수료 정책에 따라 보상으로 돌려 받습니다. 이는 평소에도 회사 계정 서버 외에도 여러 계정 서버가 탄생하고 유지될 수 있는 인센티브를 제공해주며 유저에게 선택권을 제공하고 탈중앙성을 유지하게 됩니다. 
 
 즉, 유저는 자신이 사용하지 않은 계정의 자원을 EOS-Wonderful에 제공함으로서 “채굴”이 가능해지고, 보상을 받습니다. 궁극적으로는 생태계의 발전에 이바지하게 됩니다.
# 프로젝트 요약 - bancor를 이용한 비상장 거래 방법

## 목적
상장이 되지 않은 상태에서도 사용자가 코인을 현금화하거나, 현금을 가진 투자자가 코인을 구매할 수 있는 환경을 구성하여 법정화폐간의 유동성을 확보합니다.
## 목표
**코인** - 이오스간 교환에서 단순 교환비율을 정하고 교환을 해주는 경우 코인 가격의 유동성이 사라지며 코인 가격이 이오스 가격에 절대적인 영향을 받게됩니다. 코인 자체의 가치 상승에 해가 될 수 있으며, 이오스 고래에게 대비하기 힘들어집니다. 비록 거래소에 상장되진 않아도, 거래소에 상장된것과 마찬가지로 수요와 공급에 따라 코인의 가치가 시장원리를 따르도록 만들어야합니다. 하지만 일반적인 탈중앙화 거래소를 만드는 경우 코인의 판매자와 구매자가 매칭 돼기 위한 ‘오더북’이 필요합니다. 오더북의 구조상 트래픽 소모가 심하기 때문에 구현에 문제가 생기게 됩니다. 오더북이 없으면서도 시장원리에 따라 가격이 조정되는 거래소가 필요합니다.
## 솔루션
이오스 내의 램마켓에서는 한정적인 자원을 시장원리에 따라 판매/구매하기 위해 사용됐던 BANCOR 프로토콜을 적용합니다. 이오스 블록체인 상에서 이오스 코인과 커피코인을 자유롭게 교환할 수 있는 뱅코 거래소를 스마트컨트랙으로 탈중앙-구현하게 됩니다.
## 프로젝트 개요
### EOS-RAM 마켓에 대하여
먼저, 뱅코르 프로토콜의 쉬운 이해를 위해, 이오스내의 자원 분배 방식과 램 마켓에 대해 간단히 설명하겠습니다. 이오스 자원은 CPU/NET/RAM 3종류가 있습니다. 시피유나 네트워크는 사용한다고 사라지는것이 아니며, 덜 사용한다고 해서 대역폭이 늘어나진 않습니다. 예를들어 초당 1000개의 트랜잭션이 처리가 가능한 경우, N초일때 500번의 트랜잭션을 처리했다고해서 N+1초일때 1500번의 트랜잭션을 처리할 수 있지는 않습니다. 즉 cpu나 ram은 단위시간마다 초기화되는 자원입니다. 하지만 램은 다릅니다. 램은 ‘시간’마다 초기화되는것이 아닙니다. 램은 데이터가 저장되는 공간이며, 시피유나 네트워크처럼 다이나믹하게 분배되는 경우, 램을 이미 다 사용한 사용자는 데이터가 소실되고 결국 블록체인의 무결성이 손상됩니다. 램은 아주 한정되고 희귀한 자원이라고 볼 수 있습니다. 동시에 계정 생성, 토큰 전송, 에어드랍이나 각종 댑 사용 혹은 스마트컨트랙트 업로드 등 수 많은 곳에 사용되는 매우 중요한 자원입니다. 그렇기 때문에 램 가격이 너무 싸게 고정되는 경우, 악위적인 이오스 고래가 램을 독점하는 현상이 생길 수 있으며, 램 가격이 너무 높은 경우 일반적인 사용자가 지불할 비용이 너무 높을 수 있습니다. 이 경우 이오스 블록체인의 효용성이 떨어지게 됩니다. 둘 다 이오스 블록체인의 가치를 하락시키는 원인이 됩니다. 램 가격과 법정화폐 사이의 가격은 시장원리에 따라 안정돼야하기 때문에, 램과 이오스의 교환 비율이 일정한 경우 이오스 가격이 램의 가치를 따라가게 됩니다. 이오스가 비싼 경우, 램 가격이 비싸지고 사용성이 떨어져 이오스 가격이 하락합니다. 반대로  경우 사용성이 높아져 이오스 가격이 올라갑니다... 이렇게 이오스 가격이 램에 절대적인 영향을 받게되고, 결국 램의 가격은 변동됩니다. 이것을 막기 위해 램과 이오스 간의 교환 비율은 시장원리에 따라 조정돼야합니다.

이오스 재단에서는 램을 판매하는 스마트컨트랙 계정을 만든 뒤, 해당 계정이 가진 판매분의 램의 양의 따라 가격이 조정되게 만들었습니다. 계정에 여유램이 너무 많이 남는 경우 더 싸게 판매하거나 구매하고, 여유램이 부족한 경우 비싸게 구매하고 판매합니다. 결과적으로 이오스내에 여유램이 부족한 경우 램의 가격이 비싸져서, 램을 가지고있지만 사용하지 않는 유저들의 매도압력을 높혀 램을 확보합니다. 반대로 여유램이 너무 남는 경우 램을 싸게 구매하도록하여 사용자 접근성을 높힙니다. 이렇게 램은 실제 램이 가져야할 가치를 따라가게 됩니다. 한가지 주의할 점은, 램 계정이 가지고있는 돈은 램 계정 소유주의 소유가 아닙니다. 이후 램을 판매하는 사람들에게 이오스를 돌려줘야하기 때문입니다. 램은 이오스를 사용하는 사람들에게 고루 분배돼야하는 자원이지, 특정 주체가 수입을 얻기 위해 판매하는 자원이 아닙니다.
### 뱅코를 적용한 커피코인 거래소 - 코코뱅코
커피코인도 마찬가지입니다. 코코-뱅코는 ICO를 위한것이 아닙니다. 실제 시장원리에 따라 거래가 가능하도록 하는것이 목적입니다. 발행되는 모든 코인은 코코-뱅코에 저장됩니다. 사용자는 코코-뱅코에 이오스를 보내는 경우 코인을, 코인을 보내는 경우 이오스를 받습니다. 코코-뱅코가 가진 코인의 갯수가 적어질 수록 코인의 가격은 높아집니다. 그렇기 때문에 코인을 소유한 사람들은 더 비싸게 팔 수 있게 돼어 매도 압력이 증가하고, 코코뱅코가 가진 코인이 너무 많은 경우 코인을 싸게 팔기 때문에 매수 압력이 증가합니다. 코인의 실제 가치가 증가하는 경우에도 매수 압력이, 반대로 실제 가치가 떨어지는 경우엔 매도 압력이 증가하기 때문에 코인의 가격은 실제 가치에 수렴하게 됩니다.
# 프로젝트 요약 - 스테이블 코인에 대한 고찰

## 목적
각종 결제 시스템을 지탱하기에 유동성을 가진 일반적인 형태의 코인은 사용자에게 가격 하락에 대한 두려움을 느끼게 만들 수 있으며, 이는 생태계에 악영향을 줄 수 있습니다. 이를 방지하기 위해서 가격이 안정되는 토큰 모델을 설계합니다.
## 목표
가격 하락에 대한 두려움을 방지하기 위해서는, 서비스 제공자는 제공의 대가로서 얻은 코인을 즉시 현금화하는것이 해결책입니다. 그러나 이 경우 코인이 사용됨에 따라 즉시 현금화되어 생태계에서 탈출하여 코인가치가 하방압력을 받게 됩니다. 코인 홀더의 자본이 생태계 바깥으로 유출되는것을 방지하기 위해서, 현금으로 교환하지 않아도 생태계 내에서 가치 안정성을 지니는 코인을 만듭니다.
## 솔루션
스테이블 코인은 구현하기 아주 까다로운 모델입니다. 현재 시중에 있는 대부분의 스테이블 코인 모델들은 각각 문제점을 지니고 있으며, 아직 완전한 해법이 나오지 않은 상황입니다. 각각의 모델들을 분석하고, 적절한 해답을 찾기 위해 고민해 봐야 할 시기입니다.
## 프로젝트 개요
 스테이블 코인은 크게 3가지로 분류될 수 있습니다. 법정화폐를 담보로하는 코인, 혹은 암호화폐를 담보로하는 코인, 혹은 시장의 수요에 따라 공급량을 조절하는 코인, 이렇게 3가지 모델이 있습니다. 공급량을 조절하는 코인은 메커니즘이 너무 복잡하고, 결국 신뢰를 잃는 경우 폭락의 여지가 있기 때문에 차치하도록 하겠습니다. 스테이블한 코인을 위해서는 결국 “담보”가 필요합니다. 암호화폐 담보형 스테이블 코인의 원조격이라 할 수 있는 스팀달러로 예를 들겠습니다. 스팀 달러는 1달러의 가치를 유지하기 위해 탄생한 모델입니다. 스팀에서 투표를 통해 선정된 증인들이 제시한 스팀 코인의 가격을 참고하여 스팀 달러는 1달러 어치의 스팀으로 교환 될 수 있습니다. 하지만 이는 ‘최소가치 보장’이지 ‘가치 고정’이 아닙니다. 실제 스팀 달러는 1달러를 훨씬 상회하는 가격으로 거래된적이 있습니다. 그외에 보증 주체가 보유한 달러만큼의 코인을 발행하는 법정화폐 담보형 코인인 Tether나 TrueUSD도 있지만, 이 또한 1달러가 ‘최소 가치 보장’이지 ‘가치 고정’은 아닙니다. 사실 최소 가치가 보장되는 순간 사람들의 신뢰로 인해 가치가 상승하는 경우가 많습니다. 이런것을 고려하였을 때, 실제로 ‘Stable’한 코인을 만든다는 것은 아주 힘든 여정이 될 수 있습니다.
 
 개인적인 생각으로는, 정말 Stable한 코인을 만들기 위해 엄청난 시간과 노력을 쏟아 붓기 보다는, 스팀 달러의 형태를 차용하여 코코 달러같은 최소가치 보증 코인을 만드는것이 적절하다는 판단입니다. 코코 달러의 거래 가능 유무 혹은 변환 시점등을 잘 고려한다면 충분한 대안책이 될 수 있으리라 생각합니다.
# 프로젝트 요약 - bancor를 이용한 이업종 코인간 교환 방법

## 목적
이업종 코인간의 가치는 지속적으로 변동되고, 업종의 갯수가 많아짐에 따라 각 코인간의 교환 비율 설정이 어려워집니다. 탈중앙화된 형태로 제 3자 개입 없이 적절한 가치 평가와 교환이 이루어져야 합니다.
## 목표
 이업종 코인간 교환 비율이 설정된 경우, 교환 비율이 잘못됐을 때 큰 문제가 생길 수 있습니다. 또한 시장 가치가 변함에 따라 코인의 가치도 변해야 하는데, 이를 반영하기 위해서는 제 3자의 개입이 필요합니다. 인공지능을 도입하는 경우에도 자사가 개입할 수 있는 “가능성”이 생기기 때문에 블록체인 철학에 금이 갈 수 있습니다. 이를 해결하여 이업종 코인간 교환이 시장 원리에 따라 자유롭게 교환 될 수 있도록 해야합니다.
## 솔루션
이오스 내의 램마켓에서는 한정적인 자원을 시장원리에 따라 판매/구매하기 위해 사용됐던 BANCOR 프로토콜을 적용합니다. 이오스 블록체인 상에서 이오스 코인과 커피코인을 자유롭게 교환할 수 있는 뱅코 거래소를 스마트컨트랙으로 탈중앙-구현하게 됩니다.
## 프로젝트 개요
 코인간 교환 비율이 정해져있는 경우, 수치가 잘못됐을 때 높은 교환 비율을 가진 코인으로 거래하고, 그것을 다시 높은 교환 비율을 가진 코인으로 교환하는 방식으로 코인의 갯수를 불리는 어뷰징이 가능할 수 있습니다. 예를 들어, A/B/C 3개의 코인이 있으며 각각 10:5, 5:3, 3:10 코인으로 교환됩니다. 이후 A와 B 사이의 교환 비율이 9:5로 조정되는 경우, 사용자는 A->B->C->A 로 교환을 반복하여 코인의 갯수를 무제한적으로 증가시킬 수 있습니다. 코인의 종류가 더 많아지는 경우, 이러한 문제의 발생 가능성은 비약적으로 상승하게 됩니다.
 
 이러한 문제를 방지하기 위해, 거래용 중앙 코인이 필요합니다. 이를 코코-코인이라 하겠습니다. 사용자는 코인 간 교환을 하기 위해서 A->코코->B의 형태처럼 코코-코인을 거치게 됩니다. 이 경우 각 코인과 코코 코인 사이의 교환 비율만 정해지면 위에서 언급한 문제가 생기지 않고, 코코-코인을 기준으로 가격을 책정할 수 있기 때문에 모든 코인들의 가격 설정이 간편해집니다. 사실 이미 모든 코인들은 거래소에서 법정화폐나 비트코인같은 특정 코인 몇개를 중심으로 교환이 이루어지고 있기 때문에, 이는 증명된 방법이라 할 수 있습니다.
 
 그러나 또 한가지 문제가 남습니다. ‘코인간 교환 비율’을 설정하는 제 3자의 개입이 필요하기 때문입니다. 제 3자가 정한 교환 비율이 항상 정확하기는 어렵습니다. 시장 규모나 가치에 따라 정해지더라도, 그것이 사용자 입장에서는 다를 수 있습니다. 예를들어, 치킨 코인의 가치가 치킨 시장의 가치에 따라 적절하게 산정 돼었더라도, 치킨 코인 보유자 대부분이 어떠한 동기에 의해 치킨 코인을 홀드하지 않고 즉시 팔아 없애는 경우, 치킨 코인의 가치는 치킨 시장의 가치보다 낮아야 옳습니다. 이를 위해 위에서 언급됐던 ‘Bancor relay token’ 알고리즘을 적용합니다. 두개의 토큰이 교환될 때 수요와 공급에 따라 가격이 조정되는 Bancor 알고리즘과는 다르게 서로 다른 A-B 코인이 교환되기 위해 중간 코인인 코코-코인을 거치는 경우에 코코-코인과 각각의 코인간의 거래 비율을 따져 정확한 비율로 A-B간 즉시 교환이 가능합니다. 사용자 입장에서는 A를 코코-코인으로 교환하고, 다시 코코-코인으로 B로 변환하는 수고를 거치지 않아도 정확한 비율로 거래가 가능해지며, 이는 블록체인 부하와 거래 수수료를 줄이는데 일조할 수 있습니다. 또한 코코-뱅코와 연동되는 경우 이오스 코인과 각 업종 코인간의 즉각적인 교환이 가능해집니다. 이 경우, 거래소 없이도 플랫폼내의 모든 코인은 시장 가치에 따라 코코-코인을 중심으로 이오스 혹은 타업종 코인과 교환이 가능해집니다.
# 프로젝트 요약 - 국내 유수 플랫폼 블록체인과의 차별점

## 목적
EOS-Wonderful이 국내 유명 플랫폼 블록체인들보다 뛰어난 성능과 실효성을 갖도록 준비합니다.
## 목표
국내에 존재하는 여러 플랫폼 지향 블록체인들의 실태를 분석하고 문제점을 찾아 자사 플랫폼에서 동일한 문제가 생기는것을 미연에 방지합니다.
## 솔루션
보스코인, 아이콘, 베리드 외에 국내외에 어떤 플랫폼 블록체인 프로젝트들이 존재하는지 알아보고 정리해봅니다. 현재 이오스원더풀의 접근 방식이 기존의 것과는 많이 다르지만, 발생할 수 있는 문제들을 과거 플랫폼이 부딪힌 문제들을 잣대로 예상해보고 방지 할 수 있습니다. 그 과정에서 국내 플랫폼들이 아직 해결하지 못했거나 방치하고 있는 문제들에 대해 정리하여 국내 블록체인 생태계의 문제점을 정확하게 지적하는 능력을 기릅니다.

비교 및 분석은 다음과 같은 순서로 진행합니다. 우선, 해당 코인의 백서등을 참고하여 전체적인 분석을 진행합니다. 이후 분석한 비즈니스 모델에 맞는 기술 개발 방향을 미리 예상해보고, 예상한 방향과 실제 분석 대상의 기술 개발 방향을 대조 해보면서 차이점을 분석합니다. 이 경우 어떤 방법이 더 좋은지 객관적인 판단이 가능하여 좋은 방법은 차용하고, 나쁜 방법은 대비할 수 있습니다. 방향성에 대한 비교 분석이 완료되면, 실제 개발된 코드와 방향성을 대조해 봅니다. 그 과정에서 발견되는 차이점이 어떤 이유로 생겼는지 분석합니다. 개발 과정에서 더 좋은 방법을 찾은것인지, 혹은 개발 능력 부족의 결과인지 등으로 결론을 낼 수 있습니다. 이후 우리라면 어떻게 했을 지 정리해봅니다. 결과적으로 기술적인 능력의 차이점을 객관적으로 정리할 수 있습니다.
## 프로젝트 개요
작성중