<?php

class Xmlrpc_IndexController extends Zend_Controller_Action
{
    protected $_server = null;

    public function init()
    {
        // view自体は非表示
        $this->_helper->viewRenderer->setNoRender(true);
        
        $this->_server = new Zend_XmlRpc_Server();
        // クラス追加
        $this->_server->setClass('Xmlrpc_Service_Calculator', 'Calculator');
    }

    public function indexAction()
    {
        // POSTのみ許可
        if ('POST' != $_SERVER['REQUEST_METHOD']) {
            echo $this->_server->fault();
            return;
        }
        // 結果表示
        echo $this->_server->handle();
    }
}

