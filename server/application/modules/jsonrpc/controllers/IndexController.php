<?php

class Jsonrpc_IndexController extends Zend_Controller_Action
{
    protected $_server = null;
    
    public function init()
    {
        // view自体は非表示
        $this->_helper->viewRenderer->setNoRender(true);
    
        $this->_server = new Zend_Json_Server();
        // クラス追加
        $this->_server->setClass('Jsonrpc_Service_Calculator','Calculator');
    }

    public function indexAction()
    {
        if ('POST' != strtoupper(filter_input(INPUT_SERVER, 'REQUEST_METHOD'))) {
            // URLのエンドポイント及び使用するJSON-RPCのバージョンを示します:
            $this->_server->setTarget('/jsonrpc')
                   ->setEnvelope(Zend_Json_Server_Smd::ENV_JSONRPC_2);

            // SMDをつかみます
            $smd = $this->_server->getServiceMap();

            // クライアントにSMDを返します
            header('Content-Type: application/json');
            echo $smd;
            return;
        }
        
        $this->_server->handle();
    }
}

