$(function(){
	function book() {
				// $.get('../cgi-bin/writecfg.cgi',{
				// 	para: window.localStorage.getItem('sessionid'),
				// 	rpcuser:$('#rpcName').val(),
				// 	rpcpassword:$('#rpcPwd').val(),
				// 	masternode:$('#featureCode').val(),
				// 	addnode:$('#addIp').val(),
				// 	certificate:$('#version').val(),
				// 	collateraloutputindex:$('#txIndex').val(),
				// 	collateraloutputtxid:$('#txHash').val(),
				// 	externalip:$('#ipAddress').val(),
				// 	broadcastsign:$('#nodeSign').val(),
				// 	uctpubkey1:$('#publicKey').val(),
				// 	certifiperiod:$('#timestamp').val()
				// },function(data){

				// })
				$.ajax({
					url:'../cgi-bin/writecfg.cgi?para='+window.localStorage.getItem('sessionid'),
					type:'POST',
					data:{					
						rpcuser:$('#rpcName').val(),
						rpcpassword:$('#rpcPwd').val(),
						masternode:$('#featureCode').val(),
						addnode:$('#addIp').val(),
						certificate:$('#version').val(),
						collateraloutputindex:$('#txIndex').val(),
						collateraloutputtxid:$('#txHash').val(),
						externalip:$('#ipAddress').val(),
						broadcastsign:$('#nodeSign').val(),
						uctpubkey1:$('#publicKey').val(),
						certifiperiod:$('#timestamp').val()

					},
					success: function(data){
						if(data.msg=='success'){
							$('#alert .modal-body').text('保存配置成功！')
							$('#alert').modal('show')
						}else if(data.session=="failed"){
							window.localStorage.removeItem('sessionid')
							window.location.href="/"
						}else {
							$('#alert .modal-body').text('保存配置失败！')
							$('#alert').modal('show')
						}
					},
					error: function(error){
						console.log('error', error);
					}
					/*headers:{
						rpcuser:$('#rpcName').val(),
						rpcpassword:$('#rpcPwd').val(),
						masternode:$('#featureCode').val(),
						addnode:$('#addIp').val(),
						certificate:$('#version').val(),
						collateraloutputindex:$('#txIndex').val(),
						collateraloutputtxid:$('#txHash').val(),
						externalip:$('#ipAddress').val(),
						broadcastsign:$('#nodeSign').val(),
						uctpubkey1:$('#publicKey').val(),
						certifiperiod:$('#timestamp').val()
					},*/

				})
			}
			function mainNodeOperate(code){
				if(code == 1){
					$.post('../cgi-bin/startnode.cgi',{},function(data){
						if(data.masternode =='start'){
							$('#myModal .content').html('正在启动主节点，<span style="rgba(255,0,0,0.7)">这可能需要几小时</span>，请根据主节点信号灯判断是否启动成功！');
							$('#myModal').modal('show')
							setTimeout(function(){
								$('#myModal').modal('hide')
							},10000)
						}
					})
				}else {
					$.post('../cgi-bin/stopnode.cgi',{},function(data){
						if(data.masternode =='stop'){
							$('#myModal .content').html('正在关闭主节点，这需要几分钟，请根据主节点信号灯判断是否关闭！');
							$('#myModal').modal('show')
							setTimeout(function(){
								$('#myModal').modal('hide')
							},10000)
						}
					})
				}
			}
			mainNodeStatus = {
				status:0,  /* 0:未启动 1：启动中 2：运行 3：关闭中 */
				operation:0 /* 0:无动作 1：启动 2：关闭*/
			}
			$.get('../cgi-bin/status.cgi',{
				para: window.localStorage.getItem('sessionid')
			},function(data){
				if(data.session!=="failed"){
					$('.checked-switch').prop('checked',data.ulord=='start')
					$('.title2 span').removeClass('gray').addClass(data.masternode=='start'?'green':'gray').text(data.masternode=='start'?'运行':'未运行')
					mainNodeStatus.status = (data.masternode=='start'?1:4)
				}else {
					window.localStorage.removeItem('sessionid')
					window.location.href="/"
				}
			})
			$('.checked-switch').on('click',function(e){
				e.preventDefault()
				switch(mainNodeStatus.status){
					case 1:
					case 3:
						break;
					case 2:
						mainNodeStatus.operation = 2
						$('#confirm .modal-body .red').text('你正在关闭主节点')
						$('#confirm').modal('show')
						break;
					case 3:
						mainNodeStatus.operation = 1
						$('#confirm .modal-body .red').text('你正在打开主节点')
						$('#confirm').modal('show')
						break;
					default:
						break;
				}
			})
			$('#continue').on('click',function(e){
				switch(mainNodeStatus.operation){

				}
			})
			$.ajax({
				url:'../cgi-bin/readcfg.cgi',
				type:'GET',
				data:"para="+window.localStorage.getItem('sessionid'),
				success:function(data){
					if(data.session!=="failed"){
						$('#rpcName').val(data.rpcuser)	/* RPC账号*/
						$('#rpcPwd').val(data.rpcpassword) /* RPC密码*/
						$('#featureCode').val(data.masternode) /* 主节点的特征码*/
						$('#addIp').val(data.addnode)	/* 额外的同步节点*/
						$('#version').val(data.certifiversion) /* 证书版本*/
						$('#txIndex').val(data.collateraloutputindex) /* 交易索引*/
						$('#txHash').val(data.collateraloutputtxid)  /* 交易哈希*/
						$('#ipAddress').val(data.externalip)  /* 公网IP*/
						$('#nodeSign').val(data.broadcastsign) /* 广播的主节点签名 */
						$('#publicKey').val(data.uctpubkey1) /*验证证书的公钥*/
						$('#timestamp').val(data.certifiperiod) /*证书到期日期*/
					}else {
						window.localStorage.removeItem('sessionid')
						window.location.href="/"
					}
					
				},
				error: function(error,txt){
					console.log('返回错误信息：',error.textStatus);
				}
			})
			$('#submitConfig').on('click', function() {
				book();
			})
			$('#switcher').on('click',function(){
				$('.switch-container').toggleClass('in')
			})
			$('#logout').on('click',function(){
				$.post('../cgi-bin/logout.cgi',{
					
				},function(data){
					console.log(data)
					window.localStorage.removeItem('sessionid')
					// window.location.href = '/'
				})
			})
		})
