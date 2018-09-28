# eos-wonderful
EOS-wonderful API and DEMO 


# 설명 
이오스원더풀은 이중검증 스마트컨트랙을 기반으로 하여금, 탈중앙성을 잃지 않아도 퍼블릭 블록체인인 이오스 메인넷 계정없이 이오스를 사용할 수 있도록 한다.

현재 지원되는 기능은 최소 구현 기능으로서, 구현 가능한 수준에서 목표하고 있는 사양에 훨씬 못미치고 있다. 현재 지원하는 기능은 계정 없이 토큰을 전송하는 수준이지만, 현재 수준으로도 현존하는 대부분의 댑을 지원할 수 있다. 서비스 제공자의 계정을 블록체인 내에서 자원을 소모하는 계정으로 사용하지만, 추후에는 탈중앙성을 위해 누구든지 자신의 계정을 이오스원더풀에 귀속해 잉여 자원을 소모하고 보상을 받을 수 있을것이다.

# 사용 설명
#### 이오스원더풀 기반의 댑 제작을 위해서 숙지할 것은 다음과 같다.
2. 이오스원더풀 스마트컨트랙트 계정
3. 서버에 연동될 자원 소모 계정과 API 서버
4. 서버와 연동되는 dApp 클라이언트 SDK

스마트컨트랙트 계정(Smart-contract Account, 이하 CA)은 실제 유저들의 토큰과 수수료 등 모든 정보들이 올라가는 계정입니다. 현재 진행 단계에서는 유저당 210 바이트 미만의 램을 소모합니다. CA의 멀티시그는 개발진 판단에 따라 분권화 혹은 탈중앙화가 가능하며, 직접적으로 시피유나 네트워크 자원을 소모하지는 않습니다. 전송 수수료 홀딩(추후 설명)등 사용 수수료 부과 방식을 지정할 수 있습니다.

자원 소모 계정(bandwidth Service Account, 이하 SA)은 실제로 자원을 소모하는 계정입니다. 경우에 따라서 CA가 SA 역할을 할 수 있습니다. ~~다음 개발 단계에서는 SA는 자원을 소모하는 대신 사용자 동의하에 계정주가 설정한 만큼의 수수료를 얻을 수 있습니다.~~ 현재는 SA를 대상으로 하는 DOS 공격을 방지하기 위해 수수료-홀딩 방식을 사용합니다. 사용자가 발생시키는 트랜잭션의 서명은 SA 계정의 서명이기 때문에, 사용자는 계정 해킹의 위험없이 안전하게 계정을 제공하기 위해 API 서버를 구축해야합니다. 현재로서는 일반 사용자가 접근하기엔 어려운 영역이지만, 이후 일반인도 쉽게 가능하도록 사용자 경험을 최적화할 예정입니다.

사용자가 수수료를 지불하고 SA 계정을 사용하기 위해서는 SA API SERVER와 연결하고 정해진 프로토콜에 맞춰 액션 데이터를생성해야 합니다. 이것을 간편하게 구현하기 위해서 EOSJS 기반의 클라이언트 SDK를 사용합니다.

# 사용 예시
### 1. CA(원더풀), SA(원더풀), dApp(원더풀). - 데모 사용
간단한 테스트를 위해 원더풀플랫폼에서 구현해 놓은 데모용 CA와 SA로 구성된 가상 댑을 이용합니다. 이 경우 모든 사용자 데이터는 데모용 서버에 연동됩니다.
### 2. CA(원더풀), SA(원더풀), dApp(직접 개발) - 데모 서버에서 dApp 구현
직접 dApp을 개발하고 데모용 원더풀 SA에 연결합니다.
### 3. CA(원더풀), SA,dApp(직접 구축) - 직접 구현한 dApp이 연결할 SA 구축
자신의 계정을 SA화하고 데모용 원더풀 CA와 연동합니다. 이후 dApp을 직접 구축한 SA에 연결합니다.
### 4. CA,SA,dApp(직접 구축) - 직접 이오스 원더풀 멀티버스 구현
데모용 서버를 사용하지 않고 완전히 별개의 이오스원더풀 기반 멀티버스를 구축하여 사용합니다. 수수료 홀딩량과 홀딩시간을 직접 설정할 수 있으며, 발행량 및 전체적인 컨센서스를 직접 코딩할 수 있습니다. CA는 유저당 210바이트 미만의 램외에도 스마트컨트랙트를 업로드하기 위해 약 700KB 미만의 램을 소모하기 때문에 램이 충분히 확보되어야 합니다.

# 저작권 Licence
(C) 2018. Suntae Kim all rights reserved. All Page content is property of Suntae Kim

이 저작물은 [CC BY-NC-SA 2.0 KR](https://creativecommons.org/licenses/by-nc-sa/2.0/kr/)에 따라 이용할 수 있습니다. (단, 라이선스가 명시된 일부 문서 및 삽화 제외)
