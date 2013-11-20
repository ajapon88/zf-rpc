<?php

class Jsonrpc_IndexController extends Zend_Controller_Action
{

    public function init()
    {
        $this->_helper->viewRenderer->setNoRender(true);
    
        $this->server = new Zend_Json_Server();
        $this->server->setClass('Jsonrpc_Service_Calculator','Calculator');
    }

    public function indexAction()
    {
        if ('POST' != strtoupper(filter_input(INPUT_SERVER, 'REQUEST_METHOD'))) {
            // URLのエンドポイント及び使用するJSON-RPCのバージョンを示します:
            $this->server->setTarget('/jsonrpc')
                   ->setEnvelope(Zend_Json_Server_Smd::ENV_JSONRPC_2);

            // SMDをつかみます
            $smd = $this->server->getServiceMap();

            // クライアントにSMDを返します
            header('Content-Type: application/json');
            echo $smd;
            return;
        }
        
        $this->server->handle();
    }
}

