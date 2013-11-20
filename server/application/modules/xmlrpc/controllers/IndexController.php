<?php

class Xmlrpc_IndexController extends Zend_Controller_Action
{
    protected $server = null;

    public function init()
    {
        // view自体は非表示
        $this->_helper->viewRenderer->setNoRender(true);
        $a = new Xmlrpc_Service_Calculator();
        $this->server = new Zend_XmlRpc_Server();
        // クラス追加
        $this->server->setClass('Xmlrpc_Service_Calculator', 'Calculator');
    }

    public function indexAction()
    {
        // POSTのみ許可
        if ('POST' != $_SERVER['REQUEST_METHOD']) {
            echo $this->server->fault();
            return;
        }
        // 結果表示
        echo $this->server->handle();
    }


}

